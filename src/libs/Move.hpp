struct Move{
    int fileFrom;
    int rankFrom;
    int fileTo;
    int rankTo;

    int promotion = 0;

    bool operator==(const Move cMove);
};
