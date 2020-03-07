#ifndef ConsoleView_H
#define ConsoleView_H

#include "Viewer.h"

class ConsoleView : public Viewer
{
    public:
        virtual void Reset() override;
        virtual void displayState(GameState& state) override;
        virtual void displayMessage(std::string& s) override;
        virtual void displayWinningMessage(GameState& state) override;
        virtual void displayLosingMessage(GameState& state) override;
};

#endif // ConsoleView_H

