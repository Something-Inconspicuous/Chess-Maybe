#ifndef MOVE_HPP
#define MOVE_HPP

struct Move{
    int fileFrom;
    int rankFrom;
    int fileTo;
    int rankTo;

    int promotion = 0;

    bool operator==(const Move cMove);

    void operator=(const Move nMove);
};
#endif