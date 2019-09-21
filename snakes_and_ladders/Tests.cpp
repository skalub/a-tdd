//
// Created by Sridhar Kalubandi on 2019-09-21.
//

#include <map>
#include <cstdint>
#include "catch.hpp"

struct Portal {
    enum class Type { Snake, Ladder };
    Type type;
    uint32_t target;
};

struct Action {
    enum class Type { MoveTo, Win };
    Type type;
    uint32_t target;
};
bool operator== (const Action& a1, const Action& a2)
{
    return  (a1.type == a2.type && a1.target == a2.target);
}

class Board {

    std::map<uint32_t, Portal> portals =
            {
                    { 2, { Portal::Type::Ladder, 38 } },
                    { 4, { Portal::Type::Ladder, 14 } },
                    { 8, { Portal::Type::Ladder, 31 } },
                    { 21, { Portal::Type::Ladder, 42 } },
                    { 28, { Portal::Type::Ladder, 84 } },
                    { 36, { Portal::Type::Ladder, 44 } },
                    { 47, { Portal::Type::Snake, 26 } },
                    { 49, { Portal::Type::Snake, 11 } },
                    { 51, { Portal::Type::Ladder, 67 } },
                    { 56, { Portal::Type::Snake, 53 } },
                    { 62, { Portal::Type::Snake, 18 } },
                    { 64, { Portal::Type::Snake, 60 } },
                    { 71, { Portal::Type::Ladder, 91 } },
                    { 80, { Portal::Type::Ladder, 100 } },
                    { 87, { Portal::Type::Snake, 24 } },
                    { 93, { Portal::Type::Snake, 73 } },
                    { 95, { Portal::Type::Snake, 75 } },
                    { 98, { Portal::Type::Snake, 78 } }
            };
    static const uint32_t size = 100;
public:
    auto landOn(u_int32_t square) -> Action  {
        uint32_t finalSquare = [square, this]{
            auto it = portals.find (square);
            if (portals.end() == it )
                return square;
            else
                return it->second.target;
        }();
        if (finalSquare == size)
            return Action {Action::Type::Win, square};
        else
            return Action { Action::Type::MoveTo, finalSquare};
    }
};

TEST_CASE("snakes & ladders") {
    Board board;
    // Use assignment operatior on Action type
    REQUIRE(board.landOn(1) == Action {Action::Type::MoveTo, 1});
    REQUIRE(board.landOn(1).target == 1);
    REQUIRE(board.landOn(3).target == 3);
    REQUIRE(board.landOn(2).target == 38);
    REQUIRE(board.landOn(47).target == 26);
    REQUIRE(board.landOn(100).type == Action::Type::Win);


}
