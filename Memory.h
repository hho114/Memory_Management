
#pragma once

struct FRAME{
    // 1 if assigned to process, otherwise 0
    int assigned;
    char location[40];
    int proc_assign;
    int page_num;
};


 struct frame_list {
    FRAME* frames;
    int number_of_frames;
    int page_size;
};
