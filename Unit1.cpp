//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

float x=5;
float y=5;
int numberOfBallBounces=0;
int leftPlayerPoints=0;
int rightPlayerPoints=0;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TForm1::L_upTimer(TObject *Sender)
{
        if(paddleLeft->Top > 5) paddleLeft->Top -=5;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::L_downTimer(TObject *Sender)
{
        if(paddleLeft->Top+paddleLeft->Height < background->Height-5) paddleLeft->Top  +=5;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
      if(Key=='A') L_up->Enabled=true;

      if(Key=='Z')   L_down->Enabled=true;

      if(Key==VK_UP)  R_up->Enabled=true;

      if(Key==VK_DOWN) R_down->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
      if(Key=='A') L_up->Enabled=false;

      if(Key=='Z')   L_down->Enabled=false;

      if(Key==VK_UP)  R_up->Enabled=false;

      if(Key==VK_DOWN) R_down->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::R_upTimer(TObject *Sender)
{
        if(paddleRight->Top > 5) paddleRight->Top -= 5;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::R_downTimer(TObject *Sender)
{
        if(paddleRight->Top+paddleRight->Height < background->Height-5) paddleRight->Top += 5;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_ballTimer(TObject *Sender)
{
        ball->Left += x;
        ball->Top += y;

        //odbijaj od g?rnej sciany

        if(ball->Top <= 0) y=-y;

        //odbijaj od dolnej sciany
        if(ball->Top + ball->Height >= background->Height) y=-y;

        //skucha gracza lewego
        if (( ball->Left < paddleLeft->Left   &&
        (ball->Top + ball->Height / 2 < paddleLeft->Top ||
        ball->Top + ball->Height / 2 > paddleLeft->Top + paddleLeft->Height)))
        {
                Timer_ball->Enabled=false;
                ball->Visible=false;
                rightPlayerPoints ++;
                Label1->Caption = "Punkt dla gracza prawego =>";
                Label1->Visible = true;
                Label2->Caption = IntToStr(leftPlayerPoints) +" : " + IntToStr(rightPlayerPoints);
                Label2->Visible = true;
                Label3->Caption = "Ilo?? odbi?: "+ IntToStr(numberOfBallBounces);
                Label3->Visible = true;
                Button1->Visible=true;
                Button2->Visible=true;
        }
        //skucha gracza prawego;
        if ((ball->Left + ball->Width > paddleRight->Left + paddleRight->Width &&
        (ball->Top + ball->Height / 2 < paddleRight->Top ||
        ball->Top + ball->Height / 2 > paddleRight->Top + paddleRight->Height)))
        {
                Timer_ball->Enabled=false;
                ball->Visible=false;
                leftPlayerPoints ++;
                Label1->Caption= "<= Punkt dla gracza lewego";
                Label1->Visible=true;
                Label2->Caption= IntToStr(leftPlayerPoints) +" : " + IntToStr(rightPlayerPoints);
                Label2->Visible=true;
                Label3->Caption = "Ilo?? odbi?: "+ IntToStr(numberOfBallBounces);
                Label3->Visible = true;
                 Button2->Visible=true;
                 Button1->Visible=true;

        }
        //odbicie od paletki lewej
        else if ((ball->Left < paddleLeft->Left + paddleLeft->Width &&
           ball->Top + ball->Height/2 <= paddleLeft->Top + paddleLeft->Height &&
           ball->Top + ball->Height/2 >= paddleLeft->Top))
            {
                x = 1.1 * x;
                numberOfBallBounces++;
                if(x < 0)
                {
                        //Strefa g?rna
                        if ((ball->Left <= paddleLeft->Left + paddleLeft->Width &&
                        ball->Top + ball->Height/2 < paddleLeft->Top + paddleLeft->Height/3 &&
                        ball->Top + ball->Height/2 >= paddleLeft->Top))
                        {
                                x = -  0.9 * x;
                                y = 0.9 * y;
                        }

                        //strefa srodkowa
                        else if ((ball->Left <= paddleLeft->Left + paddleLeft->Width &&
                        ball->Top + ball->Height/2 <= paddleLeft->Top + 2 * paddleLeft->Height/3 &&
                        ball->Top + ball->Height/2 >= paddleLeft->Top + paddleLeft->Height/3))
                        {
                                x = - x;
                        }
                        //strefa dolne
                        else if ((ball->Left <= paddleLeft->Left + paddleLeft->Width &&
                        ball->Top + ball->Height/2 <= paddleLeft->Top +  paddleLeft->Height &&
                        ball->Top + ball->Height/2 > paddleLeft->Top + 2/3 * paddleLeft->Height))
                        {
                                x = -1.2 * x;
                                y = 1.2 * y;
                        }

        } }
        //odbicie od paletki prawej;
        else if ((ball->Left + ball->Width >= paddleRight->Left  &&
           ball->Top + ball->Height/2 <= paddleRight->Top + paddleRight->Height &&
           ball->Top + ball->Height/2 >= paddleRight->Top))
           {
                x =  1.1 * x;
                numberOfBallBounces++;

                if(x > 0)
                {
                        //Strefa g?rna
                        if ((ball->Left + ball->Width >= paddleRight->Left &&
                        ball->Top + ball->Height/2 < paddleRight->Top + paddleRight->Height/3 &&
                        ball->Top + ball->Height/2 >= paddleRight->Top))
                        {
                                x = -  0.9 * x;
                                y = 0.9 * y;
                        }

                        //strefa srodkowa
                        else if ((ball->Left <= paddleRight->Left + paddleRight->Width &&
                        ball->Top + ball->Height/2 <= paddleRight->Top + 2 * paddleRight->Height/3 &&
                        ball->Top + ball->Height/2 >= paddleRight->Top + paddleRight->Height/3))
                        {
                                x = - x;
                        }
                        //strefa dolna
                        else if ((ball->Left <= paddleRight->Left + paddleRight->Width &&
                        ball->Top + ball->Height/2 <= paddleRight->Top +  paddleRight->Height &&
                        ball->Top + ball->Height/2 > paddleRight->Top + 2/3 * paddleRight->Height))
                        {
                                x = -1.2 * x;
                                y = 1.2 * y;
                        }
           }
           }
           }

//---------------------------------------------------------------------------



void __fastcall TForm1::Button2Click(TObject *Sender)
{
if(Application->MessageBox(
"Czy na pewno chcesz rozpocz?? od nowa?", "Potwierd?",
MB_YESNO | MB_ICONQUESTION) == IDYES)
{
Timer_ball->Enabled = true;
ball->Top = 216;
ball->Left = 480;
paddleLeft->Top = 136;
paddleRight->Top = 136;
x=5; y=5;
Label1->Visible = false;
Label2->Visible = false;
Label3->Visible = false;
Button2->Visible = false;
Button1->Visible = false;
ball->Visible = true;
leftPlayerPoints = 0;
rightPlayerPoints = 0;
numberOfBallBounces = 0;
}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
Label1->Visible = false;
Label2->Visible = false;
Label3->Visible = false;
Button2->Visible = false;
Button1->Visible = false;
numberOfBallBounces = 0;
ball->Top = 216;
ball->Left = 480;
paddleLeft->Top = 136;
paddleRight->Top = 136;
x=5; y=5;
ball->Visible = true;
Timer_ball-> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
   Application->MessageBoxA(
   "Witaj w grze PingPong!\n\n"

   "Lewy gracz steruje paletk? klawiszami A(g?ra) i Z (d??).\n"
   "Prawy gracz steruje paletk? za pomoc? strza?ek g?ra i d??. \n\n"

   "Dla urozmaicenia zabawy:\n"
   "Kiedy obijesz pi?k? na ?rodku paletki, w?wczas zmienisz jej k?t odbicia i pi?ka przy?pieszy.\n"
   "Im d?u?ej odbijasz, tym pi?ka szybciej przemieszcza si?.\n"
   "Mo?esz dowolnie zmienia? pole gry!\n \n"

   "Mi?ej zabawy!", "PingPong",MB_OK);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)
{
Label4->Visible = false;
Button3->Visible = false;

Timer_ball->Enabled = true;
ball->Top = 216;
ball->Left = 480;
paddleLeft->Top = 136;
paddleRight->Top = 136;
x=5; y=5;
Label1->Visible = false;
Label2->Visible = false;
Label3->Visible = false;
Button2->Visible = false;
Button1->Visible = false;
ball->Visible = true;
leftPlayerPoints = 0;
rightPlayerPoints = 0;
numberOfBallBounces = 0;
}
//---------------------------------------------------------------------------

