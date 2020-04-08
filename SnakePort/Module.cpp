#include <pybind11/pybind11.h>
#include "HamiltonianPath.h"
#include "GameState.h"
#include "Point.h"

namespace py = pybind11;

PYBIND11_MODULE(SnakePort, m)
{
    m.doc() = "C++ library for playing snake";

    py::class_<Point> point(m, "Point");

    point.def(py::init<>())
        .def_readwrite("X", &Point::X)
        .def_readwrite("Y", &Point::Y);

    m.def("ArePointsEqual", &ArePointsEqual, "Check if two points are the same");

    py::class_<GameState> game(m, "GameState");

    py::enum_<GameState::Move>(game, "Move")
        .value("Up", GameState::Move::Up)
        .value("Left", GameState::Move::Left)
        .value("Right", GameState::Move::Right)
        .value("Down", GameState::Move::Down)
        .value("Count", GameState::Move::Count)
        .export_values();

    py::enum_<GameState::CellType>(game, "CellType")
        .value("Wall", GameState::CellType::Wall)
        .value("Open", GameState::CellType::Open)
        .value("Body", GameState::CellType::Body)
        .value("Fruit", GameState::CellType::Fruit)
        .export_values();

    py::enum_<GameState::Orientation>(game, "Orientation")
        .value("North", GameState::Orientation::North)
        .value("South", GameState::Orientation::South)
        .value("East", GameState::Orientation::East)
        .value("West", GameState::Orientation::West)
        .export_values();

    game.def(py::init<unsigned short, unsigned short>(),
        py::arg("width") = 3, py::arg("height") = 3)
        .def("Reset", &GameState::Reset)
        .def("MakeMove", &GameState::MakeMove)
        .def("IsGameWon", &GameState::IsGameWon)
        .def("IsLegalGame", &GameState::IsLegalGame)
        .def("WasFruitFoundLastTurn", &GameState::WasFruitFoundLastTurn)
        .def("GetScore", &GameState::GetScore)
        .def("GetBoardSize", &GameState::GetBoardSize)
        .def("GetSnakeSize", &GameState::GetSnakeSize)
        .def("GetBoardWidth", &GameState::GetBoardHeight)
        .def("GetBoardHeight", &GameState::GetBoardHeight)
        .def("GetFruit", &GameState::GetFruit)
        .def("GetHead", &GameState::GetHead)
        .def("GetTail", &GameState::GetTail)
        .def("GetSnakeBody", &GameState::GetSnakeBody)
        .def("GetCellType", &GameState::GetCellType)
        .def("MoveAsInt", &GameState::MoveAsInt)
        .def("CellTypeAsInt", &GameState::CellTypeAsInt)
        .def("OrientationAsInt", &GameState::OrientationAsInt)
        .def("GetOrientation", &GameState::GetOrientation);

    py::object invalidP = py::cast(InvalidGamePoint);
    m.attr("InvalidGamePoint") = invalidP;

    m.def("GetNextPoint", &GetNextPoint, "Get the next point using the given move");
   
    m.def("GetMinimalistMove", &GetMinimalistMove, "Move using only left right arrow");

    py::class_<MoveMaker> moveMaker(m, "MoveMaker");
    moveMaker.def("MakeMove", &MoveMaker::MakeMove)
             .def("Reset", &MoveMaker::Reset);


    py::class_<HamiltonianPath> ham(m, "HamiltonianPath");
    ham.def(py::init<>())
        .def("MakeMove", &HamiltonianPath::MakeMove)
        .def("Reset", &HamiltonianPath::Reset);

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif

}
