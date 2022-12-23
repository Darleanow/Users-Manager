#include "../include/system.h"
#include "../include/menu.h"


int main(int argc, char* argv[])
{
    //First, enable VT mode
    bool fSuccess = EnableVTMode();
    if (!fSuccess)
    {
        printf("Unable to enter VT processing mode. Quitting.\n");
        return -1;
    }

    //Default console init
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    //MoveWindow(console, r.left, r.top, 360, 360, TRUE); //360 width, 360 height

    //Init of struct
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    int rows;
    
    //to get width and height of the console
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    //Unsigned for security //NOT necessary
    unsigned char key_user_pressed;

    //Selection follower for the indexes
    int selected = 0;

    //Cursor hide
    cursor(0);
    
    //Input helper
    char* strhelp;

    //fake loading screen to explain a bit to the user
    fake_load(&columns, &rows);
    
    /////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////MAIN PROGRAM PART///////////////////////////////////////////

    //Main Menu Values
    char* arr_values[] = { "Add a student", "Delete/Edit student(s)", "View students", "Add a module",
        "Delete/Edit module(s)", "View modules", "Help"};

    //HELP SECTION
    char* key_binds[] = { "Enter key", "Up_Arrow key", "Down_Arrow key", "ESC key", "F4 key" };
    char* key_binds_infos[] = { 
        "Press this key on a selected element to go access to its content",
        "Press this key to select the element above the actual selected one",
        "Press this key to select the element under the actual selected one",
        "Press this key to go back to the main menu",
        "Press this key to quit the program (if in main menu)"
    };
    int help_size = sizeof(key_binds_infos) / sizeof(key_binds_infos[0]);


    //STUDENT SECTION

    //Students container -->linked_list
    List* Students_container = list_create();

    //MODULES SECTION

    //Modules container -->linked_list
    List* Modules_container = list_create();

    //Initialization of the pointer to char* pointers
    int arr_size = (int)(sizeof(arr_values) / sizeof(arr_values[0]));

    //Menu init by display
    display_options(arr_values, &selected, &columns, &rows, &arr_size);

    while (!(GetKeyState(VK_F4) < 0))
    {
        //Get current width/height of console 16*35
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        //Cursor hide (resizing window resets this)
        cursor(0);

        //if height or width changes, we clear screen and update it with the new height
        if (columns != csbi.srWindow.Right - csbi.srWindow.Left + 1 || rows != csbi.srWindow.Bottom - csbi.srWindow.Top + 1)
        {
            //Windows screen clear
            system("cls");
            //Width of the console
            columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            //Height of the console
            rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

            //Display menu borders

            //Display options for the menu
            display_options(arr_values, &selected, &columns, &rows, &arr_size);
        }

        //So screen will always refresh, _khbit checks if a key is awaiting in stdin
        if (_kbhit())
        {
            /*
                We couldn't use GetKeyState() function from Win api because of that its behaviour is different from getch()
                thus, when you press a key, it will return a value as long as key is being pressed.
                Would be useful for games but not our case, also the enter press detection was unecessary complex, thus i used keystate
            */
            //First getch
            key_user_pressed = getch();
            //for detect the function\arrow keys 
            //we must call the getch() again
            //testing if a is '0' or '0xE0'
            if (key_user_pressed == 0 || key_user_pressed == 0xE0) key_user_pressed = getch();
            if (key_user_pressed == 72) //KEYUP
            {
                if (selected == 0)
                    selected = 6;
                else
                    selected--;
                display_options(arr_values, &selected, &columns, &rows, &arr_size);
            }
            else if (key_user_pressed == 80) //KEYDOWN
            {
                if (selected == 6)
                    selected = 0;
                else
                    selected++;
                display_options(arr_values, &selected, &columns, &rows, &arr_size);
            }
            
            //Enter key press
            if (GetKeyState(VK_RETURN) < 0)
            {
                system("cls");
                if (selected == 0)
                {
                    input_menu(0, "", &columns, &rows, &selected, Students_container, Modules_container);
                    selected = 0;
                    system("cls");
                    display_options(arr_values, &selected, &columns, &rows, &arr_size);
                }
                else if (selected == 1)
                {
                    del_edit_Student(Students_container, &columns, &rows, Modules_container);
                    selected = 1;
                    system("cls");
                    display_options(arr_values, &selected, &columns, &rows, &arr_size);
                }
                else if (selected == 2)
                {
                    if (display_students(Students_container, &columns, &rows, Modules_container) != 0)
                    {
                        printf("\nPress enter to continue. . .");
                        getchar();
                    }
                    
                    selected = 2;
                    system("cls");
                    display_options(arr_values, &selected, &columns, &rows, &arr_size);
                }
                else if (selected == 3)
                {
                    input_menu(1, "", &columns, &rows, &selected, Students_container, Modules_container);
                    selected = 3;
                    system("cls");
                    display_options(arr_values, &selected, &columns, &rows, &arr_size);
                }
                else if (selected == 4)
                {
                    del_edit_Module(Modules_container,&columns, &rows, Students_container);
                    selected = 4;
                    system("cls");
                    display_options(arr_values, &selected, &columns, &rows, &arr_size);
                }
                else if (selected == 5)
                {
                    display_modules(Modules_container, &columns, &rows);
                    printf("\nPress enter to continue. . .");
                    getchar();
                    selected = 5;
                    system("cls");
                    display_options(arr_values, &selected, &columns, &rows, &arr_size);
                }
                else if (selected == 6)
                {
                    display_informations(key_binds, key_binds_infos, 1, &columns, &rows, help_size);
                    while (GetKeyState(VK_ESCAPE) >= 0)
                    {
                        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
                        if (columns != csbi.srWindow.Right - csbi.srWindow.Left + 1 || rows != csbi.srWindow.Bottom - csbi.srWindow.Top + 1)
                        {
                            //Windows screen clear
                            system("cls");
                            //Width of the console
                            columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
                            //Height of the console
                            rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

                            //Display options for the menu
                            display_informations(key_binds, key_binds_infos, 1, &columns, &rows, help_size);
                        }
                    }
                    system("cls");
                    display_options(arr_values, &selected, &columns, &rows, &arr_size);
                }
                else
                {
                    system("cls");
                    display_options(arr_values, &selected, &columns, &rows, &arr_size);
                }
            }
        }
    }
    //Clear screen when exiting
    system("cls");
    
    //Setting back console Height and Width
    MoveWindow(console, r.left, r.top, r.right, r.bottom, TRUE); 
}