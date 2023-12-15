#include <cs50.h> // Including Cs 50 library
#include <stdio.h>//Including studio library
#include <string.h>//Including the library to count the numer os chars in a string
#include <math.h>//Including the library to round up numbers

int main(void)
{
string text = get_string("Text:  ");// counting the number of chars in the string text
float s = 0;//initial value of sentences
float l = 0;//initial value of letters
float w = 0;//initial value of words
for (int x = 0, y = strlen(text); x <= y; x++)//running through the string to check if the chars are letters, and counting words and sentences
{
    if (65 <= text[x] && text[x] <= 89) // if it is a lowercase letter
    {
        l++;
    }
    else if (97 <= text[x] && text[x] <= 122) //if it's a uppercase letter
    {
        l++;
    }
    else if (text[x] == 46 || text[x] == 63 || text[x] == 33) // seeing if there is a . or ! or ? to count sentences
    {
        s++;
    }
    else if (text[x] == 32 || text[x] == '\0') // seeing if there is a space or if it's the end of the string to count words
    {
        w++;
    }
}
    float L = (l / w) * 100.0; // making the math letters/words * 100 words
    float S = (s / w) * 100.0; // making the math sentence/words * 100 words
    double grade = 0.0588 * L - 0.296 * S - 15.8; // finding the grade
    int Grade = lrintf(grade); // rounding up the grade
    if (Grade < 1) {printf("Before Grade 1\n");} // if the grade is bellow 1, say before grade 1
    else if (Grade > 16) {printf("Grade 16+\n");}// if the grade is above 16 say grade 16+
    else {printf("Grade %i\n", Grade);}// if grade is between 1 and 16 say the grade.
}