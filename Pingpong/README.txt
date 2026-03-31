Ping Pong Game (Python + Pygame)

This project is a Python-based ping pong game developed using the Pygame library, featuring real-time gameplay, player controls, and an AI-controlled opponent. The game simulates a classic table tennis experience with collision physics, scoring mechanics, and smooth animations.

Features
Real-time ball movement and collision detection
Player-controlled paddle (keyboard input)
AI-controlled opponent paddle
Score tracking for both player and CPU
Ball reset and direction randomization after each point
Smooth gameplay at 60 FPS
How It Works

The game initializes a window using Pygame and continuously runs a game loop that:

Detects player input (arrow keys)
Updates positions of the ball and paddles
Handles collisions with walls and paddles
Tracks scores and resets the ball when a point is scored
Renders all game elements on the screen

The CPU paddle follows the ball’s vertical position to simulate an AI opponent.

Controls
Up Arrow (↑) – Move paddle up
Down Arrow (↓) – Move paddle down
Close Window – Exit the game