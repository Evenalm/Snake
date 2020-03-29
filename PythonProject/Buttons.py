from arcade.gui import *
from enum import Enum

class PlayStyle(Enum):
    Normal = 1
    Minimalist = 2
    Hamiltonian = 3

class SpeedSlowest(TextButton):
    def __init__(self, game, x=0, y=0, width=100, height=40, text="Slowest", theme=None):
        super().__init__(x, y, width, height, text, theme=theme)
        self.game = game

    def on_press(self):
        self.pressed = True

    def on_release(self):
        if self.pressed:
            self.game.moveDecitionTime = 0.2
            self.pressed = False

class SpeedSlow(TextButton):
    def __init__(self, game, x=0, y=0, width=100, height=40, text="Slow", theme=None):
        super().__init__(x, y, width, height, text, theme=theme)
        self.game = game

    def on_press(self):
        self.pressed = True

    def on_release(self):
        if self.pressed:
            self.game.moveDecitionTime = 0.1
            self.pressed = False

class SpeedFast(TextButton):
    def __init__(self, game, x=0, y=0, width=100, height=40, text="Fast", theme=None):
        super().__init__(x, y, width, height, text, theme=theme)
        self.game = game

    def on_press(self):
        self.pressed = True

    def on_release(self):
        if self.pressed:
            self.game.moveDecitionTime = 0.05
            self.pressed = False

class SpeedFastest(TextButton):
    def __init__(self, game, x=0, y=0, width=100, height=40, text="Fastest", theme=None):
        super().__init__(x, y, width, height, text, theme=theme)
        self.game = game

    def on_press(self):
        self.pressed = True

    def on_release(self):
        if self.pressed:
            self.game.moveDecitionTime = 0.0
            self.pressed = False

class SizeSmall(TextButton):
    def __init__(self, game, x=0, y=0, width=100, height=40, text="Small", theme=None):
        super().__init__(x, y, width, height, text, theme=theme)
        self.game = game

    def on_press(self):
        self.pressed = True

    def on_release(self):
        if self.pressed:
            self.game.numberOfTiles = 8
            self.pressed = False

class SizeMedium(TextButton):
    def __init__(self, game, x=0, y=0, width=100, height=40, text="Medium", theme=None):
        super().__init__(x, y, width, height, text, theme=theme)
        self.game = game

    def on_press(self):
        self.pressed = True

    def on_release(self):
        if self.pressed:
            self.game.numberOfTiles = 16
            self.pressed = False

class SizeBig(TextButton):
    def __init__(self, game, x=0, y=0, width=100, height=40, text="Big", theme=None):
        super().__init__(x, y, width, height, text, theme=theme)
        self.game = game

    def on_press(self):
        self.pressed = True

    def on_release(self):
        if self.pressed:
            self.game.numberOfTiles = 32
            self.pressed = False

class PlayNormal(TextButton):
    def __init__(self, game, x=0, y=0, width=100, height=40, text="Normal", theme=None):
        super().__init__(x, y, width, height, text, theme=theme)
        self.game = game

    def on_press(self):
        self.pressed = True

    def on_release(self):
        if self.pressed:
            self.game.nextPlayStyle = PlayStyle.Normal
            self.pressed = False

class PlayMinimalist(TextButton):
    def __init__(self, game, x=0, y=0, width=100, height=40, text="Minimal", theme=None):
        super().__init__(x, y, width, height, text, theme=theme)
        self.game = game

    def on_press(self):
        self.pressed = True

    def on_release(self):
        if self.pressed:
            self.game.nextPlayStyle = PlayStyle.Minimalist
            self.pressed = False

class WatchHamiltonian(TextButton):
    def __init__(self, game, x=0, y=0, width=100, height=40, text="Old AI", theme=None):
        super().__init__(x, y, width, height, text, theme=theme)
        self.game = game

    def on_press(self):
        self.pressed = True

    def on_release(self):
        if self.pressed:
            self.game.nextPlayStyle = PlayStyle.Hamiltonian            
            self.pressed = False