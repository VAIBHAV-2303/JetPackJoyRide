#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "coin.h"
#include "fixedbeam.h"
#include "movingbeam.h"
#include "diamond.h"
#include "magnet.h"
#include "balloon.h"
#include "boomerang.h"
#include "piggy.h"
#include "flash.h"
#include "dragon.h"
#include "ring.h"
#include "display.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

Ball ball1;
Platform platform;
Background background;
Coin* coinarr;
Fixedbeam* fixedbeamarr;
Movingbeam* movingbeamarr;
Diamond* diamondarr;
Ring* ringarr;
Magnet magnet;
Balloon balloon;
Boomerang boomerang;
Piggy piggy;
Flash flash;
Dragon dragon;
Display display;

string metainfo;

int GlobalPosn=0, currScore=0, Life=3, Level=1, NUM_OF_COINS=500, NUM_OF_FIXEDBEAMS=20, NUM_OF_MOVINGBEAMS=50, NUM_OF_DIAMONDS=100, NUM_OF_RINGS=14, onRing=0;
int ticks_since_magnet_on=180, isBoomerang=0, isPiggy=0, isFlash=0, ticks_since_dragon_on=600, ringIndex;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye (0, 0, 10);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    platform.draw(VP);
    background.draw(VP);
    ball1.draw(VP);
    for(int i=0;i<NUM_OF_COINS;i++){
        if(coinarr[i].taken==0){
            coinarr[i].draw(VP);
        }
    }
    for(int i=0;i<NUM_OF_FIXEDBEAMS;i++){
    	if(fixedbeamarr[i].burning==1){
        	fixedbeamarr[i].draw(VP);
    	}
    }
    for(int i=0;i<NUM_OF_MOVINGBEAMS;i++){
    	if(movingbeamarr[i].burning==1){
        	movingbeamarr[i].draw(VP);
    	}
    }
    for(int i=0;i<NUM_OF_DIAMONDS;i++){
    	if(diamondarr[i].taken==0){
        	diamondarr[i].draw(VP);
    	}
    }
    for(int i=0;i<NUM_OF_RINGS;i++){
        ringarr[i].draw(VP);
    }

    // Magnet?
    if(rand()%2000==0 && (ticks_since_magnet_on>=180 || ticks_since_magnet_on<=-180) && Level>=2){
    	ticks_since_magnet_on=0;
    	if(rand()%2==0){
			magnet=Magnet(250, -250);
			ticks_since_magnet_on++;
			if(onRing==0){
				ball1.speedx+=500.0/abs(ball1.position.x-250.0);    		
			}
    	}   
    	else{
    		magnet=Magnet(-250, -250);
    		ticks_since_magnet_on--;
    		if(onRing==0){
    			ball1.speedx+=-500.0/abs(ball1.position.x+250.0);
    		}
    	}    	
    }
    else if(ticks_since_magnet_on<180 && ticks_since_magnet_on>-180){
    	if(ticks_since_magnet_on>0){
    		ticks_since_magnet_on++;
    	}
    	else{
    		ticks_since_magnet_on--;
    	}
    	if(abs(ticks_since_magnet_on)==180){
    		ball1.speedx=0;
    	}
    	magnet.draw(VP);
    }

    if(rand()%(5000-10*currScore)==0 && ticks_since_dragon_on>=600 && Level>=3){
        ticks_since_dragon_on=0;
        dragon=Dragon(260.0, (rand()%350)-100.0);
    }
    else if(ticks_since_dragon_on<600){
        ticks_since_dragon_on++;
        dragon.draw(VP);
    }

    if(balloon.burst==0){
    	balloon.draw(VP);
    }

    if(isBoomerang==0 && rand()%1000==0 && Level>=2){
    	system("aplay ../Sounds/boomerang.wav&");
        isBoomerang=1;
        boomerang=Boomerang(300.0);
    }
    else if(isBoomerang==1){
        boomerang.draw(VP);
    }

    if(isPiggy==0 && rand()%2000==0 && Level>=2){
        isPiggy=1;
        piggy=Piggy((rand()%450) - 150.0);
    }
    else if(isPiggy==1){
        piggy.draw(VP);
    }

    if(isFlash==0 && rand()%5000==0 && Level>=3){
        isFlash=1;
        flash=Flash((rand()%450) - 150.0);
    }
    else if(isFlash==1){
        flash.draw(VP);
    }

    display.draw(VP, screen_zoom, currScore);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);    
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int enter = glfwGetKey(window, GLFW_KEY_ENTER);

    if(enter==GLFW_PRESS && balloon.burst==1){
    	system("aplay ../Sounds/shoot.wav&");
    	balloon=Balloon(ball1.position.x+5, ball1.position.y);
    }

    if(right==GLFW_PRESS && ball1.position.x<290 && onRing==0){
        ball1.position.x+=3;
    }
    if(left==GLFW_PRESS && ball1.position.x>-200 && onRing==0){
        ball1.position.x-=3;
    }

    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    if(space==GLFW_PRESS && onRing==0){
        ball1.speed+=-0.3;
    }
    else{
        if(ball1.position.y<=-140.0){
            ball1.speed=0;
        }
        else{
            if(ball1.position.y>=290.0){
                ball1.speed=0;
                ball1.position.y--;
            }
            ball1.speed+=(3)*(1.0/20.0);
        }
    }

}

void decLife(){

    system("aplay ../Sounds/death.wav&");

	Life--;
    if(Life==0){
    	system("pkill sh");
    	system("pkill aplay");
       	printf("============================================\n");
        printf("==============Game Over!====================\n");
        printf("============================================\n");
        quit(window);
    }
    else{
        if(ball1.position.x<=0){
        	ball1.set_position(200, ball1.position.y);
        }	
        else{
        	ball1.set_position(-200, ball1.position.y);
       	}
    }
}

void tick_elements() {

    ball1.tick();
    camera_rotation_angle += 1;
    for(int i=0;i<NUM_OF_COINS;i++){
        if(coinarr[i].taken==0){
            coinarr[i].tick();
            if(abs(ball1.position.x-coinarr[i].position.x)<20 && abs(ball1.position.y-coinarr[i].position.y)<20){
            	system("aplay ../Sounds/collectcoin.wav&");
                currScore++;
                coinarr[i].taken=1;
            }
        }
    }

	for(int i=0;i<NUM_OF_DIAMONDS;i++){
        if(diamondarr[i].taken==0){
            diamondarr[i].tick();
            if(abs(ball1.position.x-diamondarr[i].position.x)<20 && abs(ball1.position.y-diamondarr[i].position.y)<15){
                system("aplay ../Sounds/Diamond.wav&");
                currScore+=3;
                diamondarr[i].taken=1;
            }
        }
    }    

    for(int i=0;i<NUM_OF_FIXEDBEAMS;i++){
    	if(fixedbeamarr[i].burning==1){
	        fixedbeamarr[i].tick();
	        if(ball1.isSafeFor==0 && detect_collision_with_beam(ball1.position.x, ball1.position.y, fixedbeamarr[i].position.x, fixedbeamarr[i].position.y, fixedbeamarr[i].angle)){
	        	decLife();
	        }
	        if(balloon.burst==0 && detect_collision_with_beam(balloon.position.x, balloon.position.y, fixedbeamarr[i].position.x, fixedbeamarr[i].position.y, fixedbeamarr[i].angle)){
	        	balloon.burst=1;
	        	fixedbeamarr[i].burning=0;
	        }
    	}
    }

    for(int i=0;i<NUM_OF_RINGS;i++){
    	ringarr[i].tick();
    	if(onRing==0 && ball1.position.y>=ringarr[i].position.y && dist(ball1.position.x, ball1.position.y, ringarr[i].position.x, ringarr[i].position.y)<=70\
    		&& dist(ball1.position.x, ball1.position.y, ringarr[i].position.x, ringarr[i].position.y)>=60){
    		ball1.isSafeFor=30+((ringarr[i].position.x-ball1.position.x)/2.0);
    		onRing=1;
    		ball1.speed=0;
    		ball1.speedx=0;
    		ringIndex=i;
    	}
    }

    if(onRing==1){
    	ball1.position.y=ringarr[ringIndex].position.y+sqrt(max(0.0, (65.0*65.0) - (ringarr[ringIndex].position.x-ball1.position.x)*(ringarr[ringIndex].position.x-ball1.position.x)));
    	if(ball1.position.x>=65.0+ringarr[ringIndex].position.x){
    		onRing=0;
    		ball1.position.y=ringarr[ringIndex].position.y;
    	}
    }

    for(int i=0;i<NUM_OF_MOVINGBEAMS;i++){
    	if(movingbeamarr[i].burning==1){
	        movingbeamarr[i].tick();
	     	if(abs(ball1.position.x-movingbeamarr[i].position.x)<=95 && abs(ball1.position.y-movingbeamarr[i].position.y)<=10 && ball1.isSafeFor==0){
	     		decLife();
	     	}
	     	if(balloon.burst==0 && abs(balloon.position.x-movingbeamarr[i].position.x)<=95 && abs(balloon.position.y-movingbeamarr[i].position.y)<=10){
                balloon.burst=1;
	        	movingbeamarr[i].burning=0;
	        }
    	}
    }
    if(balloon.burst==0){
    	balloon.tick();
    }

    if(isBoomerang==1){
        boomerang.tick();
        if(boomerang.position.x>=310){
            isBoomerang=0;
        }
        if(abs(ball1.position.x-boomerang.position.x)<=35 && abs(ball1.position.y-boomerang.position.y)<=35 && ball1.isSafeFor==0){
            system("pkill aplay");
            decLife();
            isBoomerang=0;
        }
    }

    if(isPiggy==1){
        piggy.tick();
        if(piggy.position.x<=-300.0){
            isPiggy=0;
        }
        if(abs(ball1.position.x-piggy.position.x)<=30 && abs(ball1.position.y-piggy.position.y)<=30){
            system("aplay ../Sounds/money-bag.wav&");
            currScore+=20;
            isPiggy=0;
        }
    }

    if(isFlash==1){
        flash.tick();
        if(flash.position.x<=-300.0){
            isFlash=0;
        }
        if(abs(ball1.position.x-flash.position.x)<=15 && abs(ball1.position.y-flash.position.y)<=30){
           	system("aplay ../Sounds/powerup.wav&");
            Life++;
            ball1.isSafeFor=300;
            isFlash=0;
        }
    }

    if(ticks_since_dragon_on<600){
        dragon.tick();
        if(dragon.shot==1 && abs(ball1.position.x-dragon.bombPosition.x)<=30.0 && abs(ball1.position.y-dragon.bombPosition.y)<=30.0 && ball1.isSafeFor==0){
            decLife();
            dragon.shot=0;
        }
        if(ball1.isSafeFor==0 && ball1.position.x>=250.0 && abs(ball1.position.y-dragon.position.y)<=30){
        	decLife();
        }
    }
}

float dist(float ax, float ay, float bx, float by){
	return sqrt((ax-bx)*(ax-bx)+(ay-by)*(ay-by));
}

bool detect_collision_with_beam(float objX, float objY, float beamX, float beamY, float angle){

	if(2.0*angle>=M_PI){
		if( (objX>=beamX-2.5+60.0*cos(angle) && objX<=beamX+2.5-65.0*cos(angle) && objY>=beamY-2.5-65.0*sin(angle) && objY<=beamY+2.5+65.0*sin(angle)\
			&& abs(objY+(beamX-objX)*tan(angle)-beamY)<(15.0/abs(cos(angle)))) || (dist(beamX+60.0*cos(angle), beamY+60.0*sin(angle), objX, objY)\
			+dist(beamX-60.0*cos(angle), beamY-60.0*sin(angle), objX, objY)<=80.0)){
		    return true;
		}
		return false;
	}
	else{
		if( (objX>=beamX-2.5-65.0*cos(angle) && objX<=beamX+2.5+65.0*cos(angle) && objY>=beamY-2.5-65.0*sin(angle) && objY<=beamY+2.5+65.0*sin(angle)\
			&& abs(objY+(beamX-objX)*tan(angle)-beamY)<(15.0/abs(cos(angle)))) || (dist(beamX+60.0*cos(angle), beamY+60.0*sin(angle), objX, objY)\
			+dist(beamX-60.0*cos(angle), beamY-60.0*sin(angle), objX, objY)<=80.0)){
		    return true;
		}
		return false;
	}
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
	system("`while true; do aplay ./../Sounds/bg.wav; done;`&");
	balloon.burst=1;

    display = Display(-270, 270, COLOR_GREEN);

    // Generating random coins
    coinarr=(Coin*)malloc(NUM_OF_COINS*sizeof(Coin));
    for(int i=0;i<NUM_OF_COINS;i++){
        coinarr[i]=Coin(400.0f*i, (float)(rand()%440-140));
    }

    // Generating random rings
    ringarr=(Ring*)malloc(NUM_OF_RINGS*sizeof(Ring));
    for(int i=0;i<NUM_OF_RINGS;i++){
        ringarr[i]=Ring(2000.0f*i, (float)(rand()%400-140));
    }

    // Generating random diamonds
    diamondarr=(Diamond*)malloc(NUM_OF_DIAMONDS*sizeof(Diamond));
    for(int i=0;i<NUM_OF_DIAMONDS;i++){
        diamondarr[i]=Diamond(700.0f*(i+10), (float)(rand()%440-140));
    }

    // Generating fixed beams
    fixedbeamarr=(Fixedbeam*)malloc(2*NUM_OF_FIXEDBEAMS*sizeof(Fixedbeam));
    for(int i=0;i<NUM_OF_FIXEDBEAMS;i++){
        fixedbeamarr[i]=Fixedbeam(600.0f*(i+1), (float)(rand()%400-100), (rand()/double(RAND_MAX))*PI);
    }

	for(int i=0;i<NUM_OF_FIXEDBEAMS;i++){
        fixedbeamarr[NUM_OF_FIXEDBEAMS+i]=Fixedbeam(900.0f*(i+20), (float)(rand()%400-100), (rand()/double(RAND_MAX))*PI);
    }    
    NUM_OF_FIXEDBEAMS<<=1;

    // Generating moving beams
    movingbeamarr=(Movingbeam*)malloc(2*NUM_OF_MOVINGBEAMS*sizeof(Movingbeam));
    for(int i=0;i<NUM_OF_MOVINGBEAMS;i+=2){
        movingbeamarr[i]=Movingbeam(800.0f*(i+16), (float)(rand()%440-140));
        movingbeamarr[i+1]=Movingbeam(800.0f*(i+16), (float)(rand()%440-140));
    }
    NUM_OF_MOVINGBEAMS<<=1;

    ball1 = Ball(-200, -140, COLOR_RED);
    platform = Platform(0, 0, COLOR_BLACK);
    background = Background(0, 0, COLOR_DARK_ORANGE);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 700;
    int height = 700;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {


            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            // Level Decider
            if(currScore<=10){
            	Level=1;
            }
            else if(currScore<=50){
            	Level=2;
            }
            else{
            	Level=3;
            }

            // Generating MetaInfo
            metainfo+=" Level: ";
            ostringstream str1;
            str1 << Level;
            metainfo+=str1.str();
            metainfo+=" Lives: ";
            str1.str("");
            str1.clear();
            str1 << Life;
            metainfo+=str1.str();
            glfwSetWindowTitle(window, metainfo.c_str());
            metainfo="JetPack JoyRide ";

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

// bool detect_collision(bounding_box_t a, bounding_box_t b) {
//     return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
//            (abs(a.y - b.y) * 2 < (a.height + b.height));
// }

void reset_screen() {
    float top    = screen_center_y + 300.0 / screen_zoom;
    float bottom = screen_center_y - 300.0 / screen_zoom;
    float left   = screen_center_x - 300.0 / screen_zoom;
    float right  = screen_center_x + 300.0 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.0f, 500.0f);
}
