# sendgrid_sendemail.py
# Copyright (C) 2025 Jericho Laboratory Inc.

import base64
import json
import os
from sendgrid import SendGridAPIClient
from sendgrid.helpers.mail import Mail, Attachment, FileContent, FileName, FileType, Disposition, ContentId

def create_inline_attachment(image_path, cid):
    """Creates an inline attachment with a specified content ID."""
    with open(image_path, 'rb') as f:
        data = f.read()
    encoded = base64.b64encode(data).decode()
    
    attachment = Attachment()
    attachment.file_content = FileContent(encoded)
    
    # Determine file type from the extension.
    ext = os.path.splitext(image_path)[1].lower()
    if ext == '.png':
        file_type = 'image/png'
    elif ext in ['.jpg', '.jpeg']:
        file_type = 'image/jpeg'
    else:
        file_type = 'application/octet-stream'
    attachment.file_type = FileType(file_type)
    
    attachment.file_name = FileName(os.path.basename(image_path))
    attachment.disposition = Disposition('inline')
    attachment.content_id = ContentId(cid)
    return attachment

def create_attachment(file_path, file_type='text/plain'):
    """Creates an attachment for non-inline files (e.g., text files)."""
    with open(file_path, 'rb') as f:
        data = f.read()
    encoded = base64.b64encode(data).decode()
    
    attachment = Attachment()
    attachment.file_content = FileContent(encoded)
    attachment.file_type = FileType(file_type)
    attachment.file_name = FileName(os.path.basename(file_path))
    attachment.disposition = Disposition('attachment')  # This makes it a downloadable attachment.
    return attachment

def get_file_excerpt_html(file_path, n=10):
    """
    Reads the first n lines of a text file and returns them as a single
    string with HTML <br/> tags between lines.

    :param file_path: Path to the text file.
    :param n: Number of lines to read (default 10).
    :return: HTML-formatted string with the file excerpt.
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            lines = []
            for i, line in enumerate(file):
                if i >= n:
                    break
                lines.append(line.rstrip())
        return "<br/>".join(lines)
    except Exception as e:
        return f"Error reading text file: {e}"

def sendemail(latest_files):

    # Construct the path to the config.json file
    config_path = "/home/pi/SHELF3/config.json"

    #Unpacking the values in the dictionnary provided as input
    image1_path = latest_files['.jpg']
    image2_path = latest_files['.jpeg']
    txt1_path = latest_files['.txt']

    # Create inline attachments with unique CIDs
    
    if image1_path:
        attachment1 = create_inline_attachment(image1_path, 'image1')
    else:
        print("No image found; skipping image attachment.")
        attachment1 = None
    
    #attachment1 = create_inline_attachment(image1_path, 'image1')
       
    if image2_path:
        attachment2 = create_inline_attachment(image2_path, 'image2')
    else:
        print("No image found; skipping image attachment.")
        attachment2 = None
        
    #attachment2 = create_inline_attachment(image2_path, 'image2')

    # Create an attachment for the text file.
    if txt1_path:
        txt_attachment = create_attachment(txt1_path, 'text/plain')
    else:
        print("No text found; skipping text attachment.")
        txt_attachment = None
    
    #txt_attachment = create_attachment(txt1_path, 'text/plain')
    

    #Create text sample
    if txt1_path:
        text_content = get_file_excerpt_html(txt1_path, n=10)
    else:
        text_content = "No text file found to display."

    # Read and parse the configuration file
    try:
        with open(config_path, "r") as config_file:
            config = json.load(config_file)
            # Assume config.json contains a key "destination_email"
            destination_emails = config.get("DESTINATION_EMAILS")
            unit_name = config.get("SITE")
            if not destination_emails:
                raise ValueError("destination_emails not found in config.json")
    except Exception as e:
        print(f"Error reading configuration: {e}")
        exit(1)

    # Debug: print the SendGrid API key (optional)
    print(os.environ.get('SENDGRID_API_KEY'))

    message = Mail(
        from_email='info@jericholab.com',
        to_emails=destination_emails,
        subject=(f"WIRED: Latest Data from {unit_name}"),
        html_content=f"""
            <html>
                <body>
                    <p>Hello WIRED team,</p>
                    <p>This is an automated email with the most recent data sample from: {unit_name}.</p>
                    </p>Reolink surveillance data: {image1_path}</p>
                    <img src="cid:image1" alt="First Image" style="width:500px; height:auto;"/>
                    </p>Thermal camera data: {image2_path}</p>
                    <img src="cid:image2" alt="Second Image" style="width:500px; height:auto;"/>
                    <p>RDL data: {txt1_path} </p>
                    <p>Below are the first 10 lines. Please see the attached text document for more details.</p>
                    <p>{text_content}</p>                    
                    <p></p>
                    <p>Thank you,</p>
                    <p>Jericho team</p>
                </body>
            </html>
        """
    )
# 
#     # Add image attachments to the message.
#     message.add_attachment(attachment1)
#     message.add_attachment(attachment2)
#     # Add the text file attachment to the message.
#     message.add_attachment(txt_attachment)

    if attachment1 is not None:
        message.add_attachment(attachment1)
    if attachment2 is not None:
        message.add_attachment(attachment2)
    if txt_attachment is not None:
        message.add_attachment(txt_attachment)


    try:
        sg = SendGridAPIClient(os.environ.get('SENDGRID_API_KEY'))
        response = sg.send(message)
        print(response.status_code)
        print(response.body)
        print(response.headers)
    except Exception as e:
        print(e)

if __name__ == '__main__':
    
    # Paths to your files (images, txt)
    img1_path = '/home/pi/SHELF3/destination_folder/2025-01-17_18_19.jpg'
    img2_path = '/home/pi/SHELF3/destination_folder/E05257B12B1E-2024-11-02_201430.jpeg'
    txt1_path = '/home/pi/SHELF3/destination_folder/RDL_2025-01-22_14_USB0.txt'
    
    #Create dictionnary required for standalone operation of script
    latest_files = {}
    latest_files['.jpg'] = img1_path
    latest_files['.jpeg'] = img2_path
    latest_files['.txt'] = txt1_path
        
    # Run the task every hour on the XXth minute.
    sendemail(latest_files)