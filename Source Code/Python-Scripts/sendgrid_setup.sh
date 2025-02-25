#!/bin/bash
# setup_sendgrid.sh

# Define the subfolder and virtual environment name.
VENV_DIR="sendgrid"
VENV_NAME="myenv"
VENV_PATH="$VENV_DIR/$VENV_NAME"
ENV_FILE="sendgrid-key.env"

# Step 0: Create the subfolder if it doesn't exist.
if [ ! -d "$VENV_DIR" ]; then
    echo "Creating subfolder '$VENV_DIR' for virtual environments..."
    mkdir "$VENV_DIR"
fi

# Step 1: Create a virtual environment if it doesn't exist.
if [ ! -d "$VENV_PATH" ]; then
    echo "Creating virtual environment '$VENV_NAME' in '$VENV_DIR'..."
    python3 -m venv "$VENV_PATH"
else
    echo "Virtual environment '$VENV_NAME' already exists in '$VENV_DIR'."
fi

# Step 2: Activate the virtual environment.
echo "Activating virtual environment '$VENV_NAME'..."
source "$VENV_PATH/bin/activate"

# Step 3: Install the SendGrid package.
echo "Installing SendGrid..."
pip install sendgrid

# Step 4: Ensure the environment file is in .gitignore.
if [ ! -f .gitignore ]; then
    touch .gitignore
fi

if ! grep -qx "$ENV_FILE" .gitignore; then
    echo "$ENV_FILE" >> .gitignore
    echo "Added $ENV_FILE to .gitignore."
fi

# Step 6: Source the environment file to set the variable.
echo "Sourcing $ENV_FILE to set environment variables..."
source "$ENV_FILE"

echo "Setup complete."

read -p "Press Enter to exit..."