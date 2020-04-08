import arcade
import time
from SnakePort import GameState
from SnakePort import HamiltonianPath
from SnakePort import GetMinimalistMove
from Buttons import *

class SnakeUI(arcade.Window):
    def __init__(self, title, colour, display_menu, game_size, play_style):
        self.numberOfTiles = game_size
        self.tileSize = 18
        self.gridSize = 20
        self.boxSize = 14
        self.screenOffset = self.gridSize
        self.screenWidth = self.gridSize * self.numberOfTiles + self.screenOffset
        self.screenHeight = self.screenWidth + (2 * self.gridSize)
        super().__init__(self.screenWidth, self.screenHeight, title)
        arcade.set_background_color(colour)
        self.moveDecitionTime = 0.1
        self.nextPlayStyle = play_style
        self.display_menu = display_menu
        if(self.display_menu):
            self.setup_theme()
            self.set_buttons()
        self.reset_game()
        self.isGameRunning = False

    def set_button_textures(self):
        normal = "../images/Normal.png"
        hover = "../images/Hover.png"
        clicked = "../images/Clicked.png"
        locked = "../images/Locked.png"
        self.theme.add_button_textures(normal, hover, clicked, locked)

    def setup_theme(self):
        self.theme = Theme()
        self.theme.set_font(12, arcade.color.BLACK)
        self.set_button_textures()

    def set_buttons(self):
        self.button_list.append(SpeedSlowest(self, 36, self.screenHeight - 11, 65, 25, theme=self.theme))
        self.button_list.append(SpeedSlow(self, 36, self.screenHeight - 36, 65, 25, theme=self.theme))
        self.button_list.append(SpeedFast(self, 101, self.screenHeight - 11, 65, 25, theme=self.theme))
        self.button_list.append(SpeedFastest(self, 101, self.screenHeight - 36, 65, 25, theme=self.theme))
        self.button_list.append(SizeSmall(self, 166, self.screenHeight - 11, 65, 25, theme=self.theme))
        self.button_list.append(SizeMedium(self, 166, self.screenHeight - 36, 65, 25, theme=self.theme))
        self.button_list.append(SizeBig(self, 231, self.screenHeight - 25, 65, 25, theme=self.theme))
        self.button_list.append(PlayNormal(self, 296, self.screenHeight - 11, 65, 25, theme=self.theme))
        self.button_list.append(PlayMinimalist(self, 296, self.screenHeight - 36, 65, 25, theme=self.theme))
        self.button_list.append(WatchHamiltonian(self, 361, self.screenHeight - 25, 65, 25, theme=self.theme))

    def setup(self):
        self.shape_list = arcade.ShapeElementList()
        point_list = []
        color_list = []
        for x in range(self.screenOffset, self.screenWidth,  self.gridSize):
            for y in range(self.screenOffset, self.screenWidth, self.gridSize):

                # Calculate where the four points of the rectangle where x and y are the center
                top_left = (x - (self.tileSize / 2), y + (self.tileSize / 2))
                top_right = (x + (self.tileSize / 2), y + (self.tileSize / 2))
                bottom_right = (x + (self.tileSize / 2), y - (self.tileSize / 2))
                bottom_left = (x - (self.tileSize / 2), y - (self.tileSize / 2))

                # Append points: ORDER MATTERS!
                point_list.append(top_left)
                point_list.append(top_right)
                point_list.append(bottom_right)
                point_list.append(bottom_left)

                for i in range(4):
                    color_list.append(arcade.color.CADET_GREY)

        shape = arcade.create_rectangles_filled_with_colors(point_list, color_list)
        self.shape_list.append(shape)

        #SnakeBody list        
        self.shape_list_body = arcade.ShapeElementList()
        bodyIterator = self.Game.GetSnakeSize() - 1
        while bodyIterator >= 0:
            bodyPos = self.Game.GetSnakeBody(bodyIterator)
            shape = arcade.create_rectangle_filled((bodyPos.X * self.gridSize) + self.screenOffset, (bodyPos.Y * self.gridSize) + self.screenOffset,
                                     self.boxSize, self.boxSize, arcade.color.WHITE)
            self.shape_list_body.append(shape)
            bodyIterator -= 1

    def reset_game(self):
        self.isGameRunning = True
        self.time = time.time()
        self.wasMoveMade = False
        self.moveMade = GameState.Move.Up
        self.minLastMove = GameState.Move.Up
        self.Game = GameState(self.numberOfTiles, self.numberOfTiles)
        self.hamiltonian = HamiltonianPath()
        self.playStyle = self.nextPlayStyle

        #Rescale windows and buttons
        self.rel_font_size = self.numberOfTiles / 32
        self.screenWidth = self.gridSize * self.numberOfTiles + self.screenOffset
        self.screenHeight = self.screenWidth

        displayWidth = self.screenWidth
        if(self.display_menu):
            self.screenHeight += (2 * self.gridSize)
            displayWidth = max(self.screenWidth, 400)
            self.button_list[0].center_y = self.screenHeight - 11
            self.button_list[1].center_y = self.screenHeight - 36
            self.button_list[2].center_y = self.screenHeight - 11
            self.button_list[3].center_y = self.screenHeight - 36
            self.button_list[4].center_y = self.screenHeight - 11
            self.button_list[5].center_y = self.screenHeight - 36
            self.button_list[6].center_y = self.screenHeight - 25
            self.button_list[7].center_y = self.screenHeight - 11
            self.button_list[8].center_y = self.screenHeight - 36
            self.button_list[9].center_y = self.screenHeight - 25
        
        self.set_size(displayWidth, self.screenHeight);
        self.setup()

    def on_draw(self):
        arcade.start_render()
        self.shape_list.draw()
        self.shape_list_body.draw()
        self.draw_tile(self.Game.GetFruit(), self.boxSize, arcade.color.RED_DEVIL)
        super().on_draw()

        if not self.isGameRunning:
            arcade.draw_text("Press Enter to Start", self.screenWidth/2, self.screenHeight/1.5,
                         arcade.color.GREEN_YELLOW, font_size=(50 * self.rel_font_size), anchor_x="center")
            arcade.draw_text("Buttons Change Settings", self.screenWidth/2, self.screenHeight/1.5 - (25 * self.rel_font_size ),
                         arcade.color.GREEN_YELLOW, font_size=(25 * self.rel_font_size), anchor_x="center")

    def draw_tile(self, tile, size, color):
        arcade.draw_rectangle_filled((tile.X * self.gridSize) + self.screenOffset, (tile.Y * self.gridSize) + self.screenOffset,
                                     size, size, color)

    def update(self, delta_time):
        # Check Timer for next move
        tick = time.time()
        passed_time = tick - self.time

        if  self.isGameRunning and passed_time > self.moveDecitionTime:
            self.time = tick

            # Make move
            if self.playStyle == PlayStyle.Normal:
                self.Game.MakeMove(self.moveMade)

            elif self.playStyle == PlayStyle.Minimalist:
                if self.wasMoveMade and (GameState.Move.Left == self.moveMade or GameState.Move.Right == self.moveMade):
                    self.minLastMove = GetMinimalistMove(self.Game.GetOrientation(), self.moveMade)
                         
                self.Game.MakeMove(self.minLastMove)

            else:
                self.Game.MakeMove(self.hamiltonian.MakeMove(self.Game))
                
            self.wasMoveMade = False
            self.isGameRunning = self.Game.IsLegalGame() and not self.Game.IsGameWon()


            # Update body position list for drawing
            bodyPos = self.Game.GetHead()
            shape = arcade.create_rectangle_filled((bodyPos.X * self.gridSize) + self.screenOffset, (bodyPos.Y * self.gridSize) + self.screenOffset,
                                    self.boxSize, self.boxSize, arcade.color.WHITE)
            self.shape_list_body.append(shape)

            if not self.Game.WasFruitFoundLastTurn():
                self.shape_list_body.remove(self.shape_list_body[0])

    def on_key_press(self, key, modifiers):
        if key == arcade.key.ENTER:
            self.reset_game()
            return

        if  self.isGameRunning and not self.wasMoveMade:

            if key == arcade.key.LEFT:
                self.moveMade = GameState.Move.Left

            elif key == arcade.key.RIGHT:
                self.moveMade = GameState.Move.Right

            elif key == arcade.key.UP:
                self.moveMade = GameState.Move.Up

            elif key == arcade.key.DOWN:
                self.moveMade = GameState.Move.Down

            self.wasMoveMade = True

def main():
    game = SnakeUI("Python C++ Snake", arcade.color.OXFORD_BLUE, True, 32, PlayStyle.Normal)
    arcade.run()

if __name__ == "__main__":
    main()
