#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
// #include <cmocka.h>
// #include <GLUT/glut.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#ifndef BOARDSIZE
#define BOARDSIZE 1000
#endif

#ifndef RANDMAX
#define RANDMAX 5
#endif

#ifndef EDGE
#define EDGE 1
#endif

#ifndef COMM
#define COMM 3
#endif

#ifndef opengl
#define opengl false
#endif


typedef struct node{
    double x;
    double y;
    double vx;
    double vy;
} node;

typedef struct event {
    node *point1;
    node *point2;
    double timeOfEvent;
    int type;
    int wall;
    bool valid;
    struct event *next;
    struct event *prev;
} event;

typedef struct {
    float time;
    int edge;
} edgeCol;

typedef struct {
    float time;
    int phase;
} transition;

edgeCol edgeCollision;
transition transitionPhase;

event *HEAD = NULL;
event *TAIL = NULL;

node *point1, *point2;
int quenlength = 0;
// current time of the simulation
double currentTime = 0;
bool inRange;
double lastTransition = 0;
double totalInRange = 0;

//Function prototypes
void test();
void ttoedge(node *p);
void bounce(node *p, int edge);
double distance(node *p1, node *p2);
void init();
void remove_event(event *event);
void insert_event(event *new_event);
bool pop_event();
void create_event(int type);
double ttotrans();
void statistics(double t);

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * M_PI;
    // glColor3b(0xFA, 0x0, 0x0);
    // glColor3i(9999999, 99999999, 999999999);
    glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}


// const float DEG2RAD = 3.14159/180;
void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int lineAmount = 100; //# of triangles used to draw circle
    glColor3f(1.0,1.0,0.6);


	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * M_PI;
    // printf("test\n");
	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) {
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)),
			    y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
    // printf("end\n");
}
void drawNode(float x, float y) {
    drawHollowCircle((x - 500.0)/500.0, (y - 500.0)/500.0, 0.5);
    drawFilledCircle((x - 500.0)/500.0, (y - 500.0)/500.0, 0.01);
}
int counter = 0;
void drawConnection() {
    // glColor3f(1.0,1.0,0.6);
    glColor3f(0.0, 1.0, 1.0);
    // glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2f((GLfloat)((point1->x - 500.0)/500.0), (GLfloat)((point1->y - 500.0)/500.0));
    // (point1->x - 500.0)/500.0, (point1->y - 500.0)/500.0, 0.25)
    glVertex2f((GLfloat)((point2->x - 500.0)/500.0), (GLfloat)((point2->y - 500.0)/500.0));
    glEnd();

}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (pop_event()) {
        // no more events
        if (inRange) {
            drawConnection();
        }
        drawNode(point1->x, point1->y);
        drawNode(point2->x, point2->y);
        // sleep(1);
        // break;
    } else {
        printf("Ran out after %d events\n", counter);
        exit(0);

    }

	glutSwapBuffers();
}
FILE *f;
int main(int argc, char const *argv[]) {
    int maxTime = 100000;
    int seed = time(NULL);
    printf("%d\n", seed);
    srand(seed);


    // f = popen("gnuplot", "w");
    // fprintf(f, "set term png; "
    // "set out 'beforeafter.png'\n"
    // "set xlabel 'before'\n"
    // "set ylabel 'after'\n"
    // "plot '-'\n");
    f = popen("gnuplot", "w");
    // f = fopen("./gnuplot.txt", "w");
    fprintf(f, "set term png; "
    "set out 'beforeafter.png'\n"
    "set xlabel 'time'\n"
    "set ylabel 'frequency'\n"
    "set boxwidth 10\n"
    // "binwidth=10\n"
    // "bin(x, width)=width*floor(x/width)\n"
    "bin_width = 10;\n"
    "bin_number(x) = floor(x/bin_width)\n"
    "rounded(x) = bin_width * ( bin_number(x) + 0.5 )\n"
    "plot '-' using (rounded($1)):(1) smooth frequency with boxes\n");
    // f = fopen("./gnuplot.txt", "w");
    // fprintf(f, "set term png; "
    // "set out 'beforeafter.png'\n"
    // "set xlabel 'before'\n"
    // "set ylabel 'after'\n"
    // "binwidth=7\n"
    // "bin(x,width)=width*floor(x/width)\n"
    // "plot '-' using (bin($1,binwidth) + binwidth/2):(1.0/STATS_records) smooth freq with boxes\n");

    // srand(1487467636);
    init();
    // bool opengl = false;
    if (opengl) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowPosition(100,100);
        glutInitWindowSize(1000,1000);
        glutCreateWindow("Simulation");

        // register callbacks
        glutDisplayFunc(renderScene);
        glutIdleFunc(renderScene);

        // enter GLUT event processing cycle
        glutMainLoop();
    } else {
        while (pop_event() && currentTime < maxTime) {
            counter ++;
        }
        if (currentTime < maxTime) {
            printf("Ran out after %d events\n", counter);
            exit(0);
        }
        printf("simulation complete. Ran for %ds completing %d events\n", maxTime, counter);
        // if (pop_event()) {
        //     // sleep(1);
        //     // break;
        // } else {
        //
        // }
    }
    // simulation will run for 1000 events
    // while (counter++ < 500000) {
    //     printf("%d\n", counter);
    //     if (!pop_event()) {
    //         // no more events
    //         printf("Ran out after %d events\n", counter);
    //         break;
    //     }
    // }
    // printf("%f\n", 100*totalInRange/currentTime);

    // node pointArray[2];

    // test();

    return 0;
}

void test() {
    node *point;
    point = malloc(sizeof(node));

    point->x = 200;
    point->y = 0;
    point->vx = 200;
    point->vy = 300;
    // printf("%f\n", ttoedge(point));

}
double randr(int a) {
    double random = 0;
    while (random == 0) {
        random = (double)(((double)rand()/(double)RAND_MAX) * (double)a);
    }
    return random;
}

void init() {
    point1 = malloc(sizeof(node));
    point2 = malloc(sizeof(node));
    // ((rand()%2) ? -1 : 1) * randr(RANDMAX);

    point1->x = randr(BOARDSIZE);
    point1->y = randr(BOARDSIZE);
    point1->vx = ((rand()%2) ? -1 : 1) * randr(RANDMAX);
    point1->vy = ((rand()%2) ? -1 : 1) * randr(RANDMAX);

    point2->x = randr(BOARDSIZE);
    point2->y = randr(BOARDSIZE);
    point2->vx = ((rand()%2) ? -1 : 1) * randr(RANDMAX);
    point2->vy = ((rand()%2) ? -1 : 1) * randr(RANDMAX);

    // printf("init:: x1: %f, y1: %f, x2: %f, y2: %f,",point1->x, point1->y,  point2->x,  point2->y);
    // printf("vx1: %f, vy1: %f, vx2: %f, vy2: %f\n",point1->vx, point1->vy,  point2->vx,  point2->vy);

    if (distance(point1, point2) < 250) {
        inRange = true;
    }

    create_event(1);
    create_event(2);

}



void ttoedge(node *p) {
    // double minTime = 1.0/0.0; // positive infinity
    double minTime = INFINITY;
    double newTime;
    int edge = 0;

    // if (p->vx >= 0) {
    //     (BOARDSIZE - p->x) /
    // }

    if (p->vx < 0) {
        newTime = (p->x / -p->vx);
        if (newTime < minTime && newTime >=0) {
            minTime = newTime;
            edge = 4;
        }
        // printf("newtime = %f, edge=%d\n", newTime,4);
        // printf("1, %f\n", newTime);
    } else {
        newTime = (BOARDSIZE- p->x) / p->vx;
        if (newTime < minTime && newTime >=0) {
            minTime = newTime;
            edge = 2;
        }
        // printf("newtime = %f, edge=%d\n", newTime,2);
        // printf("2, %f\n", newTime);
    }

    if (p->vy < 0) {
        newTime = p->y / -p->vy;
        if (newTime < minTime && newTime >=0) {
            minTime = newTime;
            edge = 1;
        }
        // printf("newtime = %f, edge=%d\n", newTime,1);
        // printf("3, %f\n", newTime);
    } else {
        newTime = (BOARDSIZE - p->y) / p->vy;
        if (newTime < minTime && newTime >=0) {
            minTime = newTime;
            edge = 3;
        }
        // printf("newtime = %f, edge=%d\n", newTime,3);
        // printf("4, %f\n", newTime);
    }
    // printf("tto: edge %d, x=%f, y=%f, vx=%f, vy=%f, time=%f\n", edge, p->x, p->y, p->vx, p->vy, minTime);
    edgeCollision.time = minTime;
    edgeCollision.edge = edge;
    // return edgeCol;
}

// gives a node a random velocity vector upon wall collision
void bounce(node *p, int edge) {
    // printf("AHHHHHHHHH\n");

    switch (edge) {
        case 1:
            p->vx = ((rand()%2) ? -1 : 1) * randr(RANDMAX);
            p->vy = randr(RANDMAX);
        break;
        case 2:
            p->vx = -randr(RANDMAX);
            p->vy = ((rand()%2) ? -1 : 1) * randr(RANDMAX);
        break;
        case 3:
            p->vx = ((rand()%2) ? -1 : 1) * randr(RANDMAX);
            p->vy = -randr(RANDMAX);
        break;
        case 4:
            p->vx = randr(RANDMAX);
            p->vy = ((rand()%2) ? -1 : 1) * randr(RANDMAX);
        break;

    }
    // bool changed = false;
    // if(p->x <= 0.01) {
    //     p->vx = randr(RANDMAX);
    //     p->vy = ((rand()%2) ? -1 : 1) * randr(RANDMAX);
    //     changed = true;
    // }
    // if (p->x >= BOARDSIZE-0.01) {
    //     p->vx = -randr(RANDMAX);
    //     p->vy = ((rand()%2) ? -1 : 1) * randr(RANDMAX);
    //     changed = true;
    // }
    // if(p->y <= 0.01) {
    //     p->vx = ((rand()%2) ? -1 : 1) * randr(RANDMAX);
    //     p->vy = randr(RANDMAX);
    //     changed = true;
    // }
    // if (p->y >= BOARDSIZE-0.01) {
    //     p->vx = ((rand()%2) ? -1 : 1) * randr(RANDMAX);
    //     p->vy = -randr(RANDMAX);
    //     changed = true;
    // }
    // if (changed) return;
    // // printf("fperror\n");
}

// Returns the euclidea distance between two nodes
double distance(node *p1, node *p2) {
    return sqrt(pow((p1->x-p2->x), 2) + pow((p1->y - p2->y), 2));
}

void update() {
    // printf("update:: x1: %f, x2: %f, y1: %f, y2: %f\n",point1->x, point1->y,  point2->x,  point2->y);
    double elapsedTime = HEAD->timeOfEvent - currentTime;
    point1->x += elapsedTime*point1->vx;
    point1->y += elapsedTime*point1->vy;
    point2->x += elapsedTime*point2->vx;
    point2->y += elapsedTime*point2->vy;
    // printf("update:: x1: %f, y1: %f, x2: %f, y2: %f\n",point1->x, point1->y,  point2->x,  point2->y);
}
// Remove and Item from the queue and handle it

void print_queue() {
    printf("QUEUE::");
    for (event *e = HEAD;e !=NULL ; e = e->next) {
        printf(" %fs,", e->timeOfEvent);
    }
    printf("end\n");
}
bool pop_event() {
    // printf("QUEUE LENGTH%d\n", quenlength);
    // print_queue();
    // no evnet to pop
    if (distance(point1, point2) > 250 && inRange && HEAD->type != 3) {
        printf("shit went south: %d\n", HEAD->type);
        // exit(1);
    }
    if (HEAD == NULL) return false;
    update();
    if (point1->x < -10 || point1->y < -10 || point2->x < -10 || point2->y > 1010 || point1->x > 1010 || point1->y > 1010 || point2->x > 1010 || point2->y > 1010) {
        printf("\nnode %d collides with wall %d\n", HEAD->type, HEAD->wall);
        printf("update:: x1: %f, y1: %f, x2: %f, y2: %f\n",point1->x, point1->y,  point2->x,  point2->y);
        printf("\t\tvx1: %f, vy1: %f, vx2: %f, vy2: %f\n",point1->vx, point1->vy,  point2->vx,  point2->vy);
        exit(0);
    }
    currentTime = HEAD->timeOfEvent;
    printf("Time = %f\n", currentTime);
    // printf("time: %f\n", currentTime);

    int eventType = HEAD->type;
    // printf("et:%d\n", eventType);
    if (eventType == 1) {
        bounce(point1, HEAD->wall);
        // remove_event(HEAD);
        // create_event(1);
    } else if (eventType == 2) {
        bounce(point2, HEAD->wall);
        // remove_event(HEAD);
        // create_event(2);

    } else if (eventType == 3) {
        if (HEAD->wall != inRange) {
            if (HEAD-> wall == 0) {
                totalInRange += currentTime - lastTransition;
                statistics(currentTime - lastTransition);

            }
        }
        // this is where we can determine if it is entering or exiting the area
        // if (inRange) {
        //     // printf("hello\n");
        //     totalInRange += currentTime - lastTransition;
        // }
        //     lastTransition = currentTime;
        // } else {
        // }
        lastTransition = currentTime;
        inRange = HEAD->wall;


        //after handling the event

    }

    remove_event(HEAD);
    create_event(eventType);

    // remove_event(HEAD);
    return true;
}

// create a new event to handle a state
void create_event(int type) {
    // if (distance(point1, point2) > 250) {
    //     inRange = false;
    // } else {
    //     inRange = true;
    // }
    if (type == 1) {
        event *new_event = malloc(sizeof(event));
        // new_event->point1
        new_event->type = 1;
        new_event->valid = true;
        // printf("ttoedge1: %f\n", ttoedge(point1));
        ttoedge(point1);
        new_event->timeOfEvent = currentTime + edgeCollision.time;
        new_event->wall = edgeCollision.edge;
        insert_event(new_event);
        // return;
    } else if (type == 2) {
        event *new_event = malloc(sizeof(event));
        new_event->type = 2;
        new_event->valid = true;
        // printf("ttoedge2: %f, vx = %f, vy = %f\n", ttoedge(point2), point2->vx, point2->vy);
        ttoedge(point2);
        new_event->timeOfEvent = currentTime + edgeCollision.time;
        new_event->wall = edgeCollision.edge;
        insert_event(new_event);
        // return;
    }
    double transition = ttotrans();
    // printf("hello\n");
    if (transition <= 0) {
        // printf("T: %f", transitionPhase.time);
        // printf("\n");
        return;
    } else {
        if (HEAD->timeOfEvent > (transitionPhase.time + currentTime) && (HEAD->type != 3 || HEAD->wall != transitionPhase.phase) ) {
            // printf("%f, %f, c:%f\n", HEAD->timeOfEvent, (timeToTransition + currentTime), currentTime);
            printf("Phase time: %f\n", transitionPhase.time);
            event *new_event = malloc(sizeof(event));
            new_event->type = 3;
            new_event->valid = true;
            new_event->wall = transitionPhase.phase;
            new_event->timeOfEvent = currentTime + transitionPhase.time;
            insert_event(new_event);
        } else {
            printf("distance befor error %f\n", distance(point1, point2));
        }
    }
}


        // this is the type of entering or exiting area of influence.
        // for loop to determine if anything happens before a bounce
        // printf("hi\n");

    // double timeToTransition = ttotrans();
    // // printf("hello\n");
    // printf("T: %f", timeToTransition);
    // if (timeToTransition <= 0.001) {
    //     printf("\n");
    //     return;
    // } else {
    //     if (HEAD->timeOfEvent > timeToTransition) {
    //         printf("here\n");
    //         event *new_event = malloc(sizeof(event));
    //         new_event->type = 3;
    //         new_event->valid = true;
    //         new_event->timeOfEvent = currentTime + timeToTransition;
    //         insert_event(new_event);
    //     }
    //
    // }
// }


double ttotrans() {
    double A, B, C, m, b, r, x, y, vx, vy, d, X, t;
    x = point2->x - point1->x;
    y = point2->y - point1->y;
    vx = point2->vx - point1->vx;
    vy = point2->vy - point1->vy;
    m = vy / vx;
    b = y - (m * x);
    r = 250;
    A = 1 + (m * m);
    B = 2 * m * b;
    C = (b * b) - (r * r);
    d = (B * B) - (4 * A * C);
    // printf("y = %fx + %f\n", m, b);
    // printf("d:%f\n", d);
    if (d < 0.001 && d > -0.001) {
        // printf("yahooo\n");
    }
    if (d < 0.001) return -1;

    if (distance(point1, point2) > 250) {
        // printf("1\n");
        transitionPhase.phase = 1;
        // X =(-B - sqrt(d)) / (2 * A);
    } else {
        // printf("0\n");
        transitionPhase.phase = 0;
        // X = (-B + sqrt(d)) / (2 * A);
    }
    // transitionPhase.time = (X - x) / vx;
    // return 1;
    // return (X - x) / vx;
    X = (-B + sqrt(d)) / (2 * A);
    // if (X > 0) return X;
    // printf("A:%f, B: %f, C:%f, %f\n", A,B,C,d);
    // return X;
    double t1 = t = (X - x) / vx;

    X = (-B - sqrt(d)) / (2 * A);
    // if (X > 0) return X;
    // printf("A:%f, B: %f, C:%f, %f\n", A,B,C,d);
    // return X;
    double t2 = (X - x) / vx;
    printf("t1:%f, t2:%f\n", t1,t2);
    if (t1 > 0.000001 && (t1 <= t2 || t2< 0.000001)) {
        printf("t1\n");
        transitionPhase.time =  t1;
        transitionPhase.phase = 0;
    } else if (t2 > 0.000001) {
        printf("t2\n");
        transitionPhase.time =  t2;
        transitionPhase.phase = 1;
    } else {
        printf("t-1\n");
        // transitionPhase.time =  1;
        return -1;
    }
    // if (t > 0.0001) {
    //     transitionPhase.phase = 1;
    //     transitionPhase.time =  t;
    // } else {
    //     X =(-B - sqrt(d)) / (2 * A);
    //     t = (X - x) / vx;
    //     if (t > 0.0001) {
    //         transitionPhase.phase = 0;
    //         transitionPhase.time =  t;
    //     } else {
    //         return -1;
    //
    //     }
    //
    // }
    // if (distance(point1, point2) > 250.00001) {
    //     printf("1\n");
    //     transitionPhase.phase = 1;
    //     // X =(-B - sqrt(d)) / (2 * A);
    // } else if (distance(point1, point2) < 249.9999)  {
    //     printf("0\n");
    //     transitionPhase.phase = 0;
    //     // X = (-B + sqrt(d)) / (2 * A);
    // }
    return 1;
}


void insert_event(event *e) {

    double it = 0;
    int i = 0;
    if (HEAD == NULL) {
        HEAD = e;
        HEAD->next = NULL;
        it = 0;
    } else if (e->timeOfEvent < HEAD->timeOfEvent){
        it = HEAD->timeOfEvent;
        e->next = HEAD;
        HEAD = e;
    } else {
        for (event *current = HEAD; ; current = current->next) {
            i++;
            if (current->next == NULL) {
                current->next = e;
                e->next = NULL;
                break;
            } else {
                if (e->timeOfEvent < current->next->timeOfEvent) {
                    it = current->next->timeOfEvent;
                    e->next = current->next;
                    current->next = e;
                    break;
                }
            }
        }
    }
    // printf("insert_event at depth %d. This %f < %f!\n", i, e->timeOfEvent, it);
}

void remove_event(event *e) {
    if (e == HEAD) {
        // HEAD == NULL;
        HEAD = HEAD->next;
    } else {
        for (event *current = HEAD; ; current = current->next) {
            if (current->next == e) {
                current->next = current->next->next;
            }
        }
    }
    free(e);
}
int statCounter = 0;
void statistics(double t) {
    // local int counter
    // fprintf(f, "%d %f\n", statCounter++, t);
    fprintf(f, "%f\n", t);
}
