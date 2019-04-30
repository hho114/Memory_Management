
#pragma once

struct frame{
    // 1 if assigned to process, otherwise 0
    int assigned;
    char location[40];
    int proc_assign;
    int page_num;
};


 struct frame_list {
    frame * frames;
    int number_of_frames;
    int page_size;
};



frame_list * createFameList(int number_of_frames, int page_size)
{
    frame_list *list;

    //returns the pointer to the beginning of newly allocated memory
    list = malloc(sizeof(frame_list));
    //allocates enough for an array of number_of_frames
    //f->frames = (FRAME*)malloc(sizeof(FRAME) * number_of_frames);
    list->frames = malloc(sizeof(FRAME) * number_of_frames);
    list->page_size = page_size;
    list->number_of_frames = number_of_frames;

    for (int i = 0; i < number_of_frames; i++) {
        list->frames[i].assigned = 0;
    }

    return list;
}

bool isEnoughMemoryForProcess(frame_list* list, process* process)
{

    for (int i = 0; i < list->number_of_frames; i++) {
        if (!list->frames[i].assigned) {
            num_free_frames += 1;
        }
    }

    // if the number of free frames * the page size is greater than the mem req
    // for the process in question we can fit it in.
    return (num_free_frames * list->page_size) >= process->mem_reqs;
}

void putProcessIntoMemory(frame_list* list, process* process)
{
    // this assumes you've already checked that you *can* fit the proc into mem
    int current_page = 1;

    int remaining_mem = proc->mem_reqs;

    for (int i = 0; i < list->number_of_frames; i++)
    {
        // if this frame is not assigned
        if (!list->frames[i].assigned)
        {
            // assign it
            list->frames[i].assigned = 1;
            // set the page number
            list->frames[i].page_num = current_page;
            // set the process number
            list->frames[i].proc_assign = proc->pid;

            current_page++;
            remaining_mem -= list->page_size;
        }

        if (remaining_mem <= 0)
        {
            break;
        }
    }
}


void printFrameList(frame_list* list)
{
    int in_free_block = 0, start;

    printf("\tMemory map:\n");

    for (int i = 0; i < list->number_of_frames; i++)
    {
        if (!in_free_block && !list->frames[i].assigned)
        {
            in_free_block = 1;
            start = i;
        }
        else if (in_free_block && list->frames[i].assigned)
        {
            in_free_block = 0;
            printf("\t\t%d-%d: Free frame(s)\n",
                   start * list->page_size,
                   (i * list->page_size) - 1);
        }


        if (list->frames[i].assigned)
        {
            printf("\t\t%d-%d: Process %d, Page %d\n",
                   i * list->page_size,
                   ((i + 1) * list->page_size) - 1,
                   list->frames[i].proc_assign,
                   list->frames[i].page_num);
        }
    }

    if (in_free_block)
    {
        printf("\t\t%d-%d: Free frame(s)\n",
               start * list->page_size,
               ((i) * list->page_size) - 1);
    }
}


bool isFrameListEmpty(frame_list* list)
{

    for (int i = 0; i < list->number_of_frames; i++)
    {
        if (list->frames[i].assigned)
        {
            return 0;
        }
    }

    return 1;
}

void FreeMemory(frame_list* list, int pid)
 {

    frame * frame;
    for (int i = 0; i < list->number_of_frames; i++)
    {
        frame = &list->frames[i];

        if (frame->proc_assign == pid)
        {
            frame->proc_assign = 0;
            frame->page_num = 0;
            frame->assigned = 0;
        }
    }
}
