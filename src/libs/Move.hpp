struct Move{
    int fileFrom;
    int rankFrom;
    int fileTo;
    int rankTo;

    bool operator==(const Move cMove);
};
