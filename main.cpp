
#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

 int width = 1200;
 int height = 700;
 float koef;
 float gravityBall = 0.002f;

struct TBall
{
   float x,y;
   float dx, dy;
   float r;
};

TBall ball;

void TBall_Init(TBall* obj, float x1, float y1, float dx1, float dy1, float r1)
{
   obj->x = x1;
   obj->y = y1;
   obj->dx = dx1;
   obj->dy = dy1;
   obj->r = r1;
}

void Game_Init()
{
   TBall_Init(&ball, 0,0,0,0, 0.2);
}

void DrawCircle(int cnt)
{
   float x,y;
   float da = M_PI * 2.0 / cnt;
   glBegin(GL_TRIANGLE_FAN);
   glVertex2f(0,0);
   for(int i = 0; i <= cnt; i++)
   {
      x = sin(da * i);
      y = cos(da * i);
      glVertex2f(x,y);
   }
   glEnd();
}

void TBall_Show(TBall obj)
{
   glPushMatrix();
   glTranslatef(obj.x, obj.y,0);
   glScalef(obj.r, obj.r,1);
   DrawCircle(20);
   glPopMatrix();
}
void TBall_Move(TBall * obj)
{
   obj->x += obj->dx;
   obj->y += obj->dy;
    
    if(obj->y < obj->r-1)
    {
      obj->dy *= -0.85;
      obj->y = obj->r - 1;
    }

   obj->dy -= gravityBall;
}

int main()
{
   if(glfwInit())
   {
    std::cout<<"OpenGl Ok\n";
    
   }else{
    std::cout<<stderr;
    glfwTerminate();
   }

   GLFWwindow* window;
   window = glfwCreateWindow(width, height, "Hernya", nullptr,nullptr);
   
   if(window==nullptr)
   {
      std::cout<<stderr<<"ErrorWindow\n";
      glfwTerminate();
   }else
   {
    std::cout<<"Window Ok\n";
   }

   glfwMakeContextCurrent(window);
   glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
   gladLoadGL();
  
 
   koef = (float)width/height;
   glScalef(1/koef, 1, 1);

   Game_Init();

do
{
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
      glClear(GL_COLOR_BUFFER_BIT);

      TBall_Move(&ball);
      
      glColor3f(1,1,0);
      TBall_Show(ball);

    glfwSwapBuffers(window);
    glfwPollEvents();

} while (glfwGetKey(window,GLFW_KEY_ESCAPE) != GLFW_PRESS &&
glfwWindowShouldClose(window)== 0 );



glfwTerminate();
    return 0;
}