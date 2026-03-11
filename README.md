Ответ Gemini
Chess-CheckMate-Detector
A C++ based chess engine component designed to identify checkmate, stalemate, and forced-mate sequences in given board states.

Features
Board Representation: Full grid-based board matrix management.

Piece Logic: Supports standard movement validation for all chess pieces (King, Queen, Rook, Bishop, Knight, Pawn).

Game State Analysis:

isCheckmate: Validates if the current side is in check and has no legal moves to escape.

isMateInOne: Performs a depth-1 search to find immediate checkmate sequences.

isMateInTwo: Performs a depth-2 exhaustive search to identify forced mate sequences.

isBoardLegal: Validates board configuration (e.g., King count, illegal check states).

How it works
The detection engine utilizes a recursive simulation approach:

Move Generation: Iterates through all legal moves for the active player.

Move Safety: Validates that a move does not leave the King in check.

Branching Search: * To identify a "Mate in 2," the engine explores all candidate player moves.

For each candidate, it simulates all possible opponent responses.

It confirms that for every defensive response, there exists a follow-up move that leads to checkmate.

Prerequisites
C++11 or higher.

Standard STL headers.

Usage
The engine works by loading a board configuration from a text-based format:

C++
ChessBoard<Piece*> board;
std::vector<std::string> setup = {
    ".......k",
    "........",
    ".....K..",
    "R.......",
    "........",
    "........",
    "........",
    "........"
};
board.loadBoard(setup);

if (board.isMateInTwo('W')) {
    // Logic for handling found mate in two
}
Project Structure
ChessBoard.h: Core logic for board state, move validation, and mate detection algorithms.

Piece.cpp / Piece.h: Base class and definitions for individual piece movement rules.

Matrix.h: Underlying grid structure.

main.cpp: Entry point for testing specific board configurations.