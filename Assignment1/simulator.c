#include "sim.h"

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
        if (slow) {
            sleep(1);
        }
        // break;
    } else {
        printf("Ran out after %d events\n", counter);
        exit(1);

    }
    if (currentTime > MAXTIME) {
        exit(0);
    }

	glutSwapBuffers();
}
FILE *f;
int main(int argc, char const *argv[]) {
    // int maxTime = 10000000;
    // exit(0);
    if (SEED) {
        srand(SEED);
    } else {
        int seed = time(NULL);
        // int seed = 1487556356;
        printf("Random seed: %d\n", seed);
        srand(seed);
    }


    // f = popen("gnuplot", "w");
    // fprintf(f, "set term png; "
    // "set out 'beforeafter.png'\n"
    // "set xlabel 'before'\n"
    // "set ylabel 'after'\n"
    // "plot '-'\n");
    f = popen("gnuplot", "w");
    // f = fopen("./gnuplot.txt", "w");
    // psy.swansea.ac.uk/staff/carter/gnuplot/gnuplot_frequency.htm -> amazing!
    fprintf(f, "set term png; "
    "set out 'frequency.png'\n"
    "set title 'Frequency Histogram of Node Encounter Duration'\n"
    "set xlabel 'Time spent in Range (simulated seconds)'\n"
    "set ylabel 'Frequency of Duration'\n"
    "set boxwidth 5 absolute\n"
    "set style fill solid 1.0 noborder\n"
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
		// Basic glut setup
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
		// run in command line mode. pop event from queue until simualtion is over
        while (pop_event() && currentTime < MAXTIME) {
            counter ++;
        }
        if (currentTime < MAXTIME) {
            printf("Ran out after %d events\n", counter);
            exit(1);
        }
        printf("simulation complete. Ran for %fs completing %d events and averaging %.2f%% in range\n", currentTime, counter, (totalInRange/currentTime)*100);

    }


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
// Function to generate floating point numbers in the specified range
double randr(int a) {
    double random = 0;
    while (random <= RANDMIN) {
        random = (double)(((double)rand()/(double)RAND_MAX) * (double)a);
    }
    // printf("%f\n", random);
    return random;
}
// initializes the points with random positions and velocities. Creates inital events on
// the priority queue
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

    if (distance(point1, point2) < RADIUS) {
        inRange = true;
    }

    create_event(1);
    create_event(2);

}


// This calculates the time to the edge as the min of the time to hit all 4 walls.
// Negative times excluded. simple t = d/v
// the return object is a struct with a time and a wall
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

}

// Returns the euclidea distance between two nodes
double distance(node *p1, node *p2) {
    return sqrt(pow((p1->x-p2->x), 2) + pow((p1->y - p2->y), 2));
}
// this moves the nodes for the time that was skipped due to simulation
void update() {
    // printf("update:: x1: %f, x2: %f, y1: %f, y2: %f\n",point1->x, point1->y,  point2->x,  point2->y);
    double elapsedTime = HEAD->timeOfEvent - currentTime;
    point1->x += elapsedTime*point1->vx;
    point1->y += elapsedTime*point1->vy;
    point2->x += elapsedTime*point2->vx;
    point2->y += elapsedTime*point2->vy;
    // printf("update:: x1: %f, y1: %f, x2: %f, y2: %f\n",point1->x, point1->y,  point2->x,  point2->y);
}

// used for debugging
void print_queue() {
    printf("QUEUE::");
    for (event *e = HEAD;e !=NULL ; e = e->next) {
        printf(" %fs,", e->timeOfEvent);
    }
    printf("end\n");
}
// pop event is the main function of the simulation. It pops an event from the queue
// and handles it appropriately.
bool pop_event() {
    // printf("QUEUE LENGTH%d\n", quenlength);
    // print_queue();
    // no evnet to pop

	// ERROR CHECKING
    if (distance(point1, point2) > (RADIUS +1) && inRange && HEAD->type != 3) {
        printf("Range error: outside\n");
        // sleep(10);
        exit(1);
    }
    if (distance(point1, point2) < (RADIUS - 1) && !inRange && HEAD->type != 3) {
        printf("Range error: inside\n");
        // sleep(10);
        exit(1);
    }
	// no more events
    if (HEAD == NULL) return false;
    update();
	// ERROR checking
    if (point1->x < -10 || point1->y < -10 || point2->x < -10 || point2->y > (BOARDSIZE + 10) || point1->x > (BOARDSIZE + 10) || point1->y > (BOARDSIZE + 10) || point2->x > (BOARDSIZE + 10) || point2->y > (BOARDSIZE + 10)) {
        printf("\nNODE LEFT AREA\nnode %d collides with wall %d\n", HEAD->type, HEAD->wall);
        printf("update:: x1: %f, y1: %f, x2: %f, y2: %f\n",point1->x, point1->y,  point2->x,  point2->y);
        printf("\t\tvx1: %f, vy1: %f, vx2: %f, vy2: %f\n",point1->vx, point1->vy,  point2->vx,  point2->vy);
        exit(1);
    }
    currentTime = HEAD->timeOfEvent;
	// Events of type 0 are for opengl rendering. They only cause updates to force smooth redering
    if (HEAD->type != 0 || ((int)currentTime % 100 == 0)) {

        // printf("Time = %f\n", currentTime);
    }
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
        counter4++;
    	// event type three are in radius changes
        if (HEAD->wall == 0) {
            totalInRange += currentTime - lastTransition;
            statistics(currentTime - lastTransition);
        } else {

            lastTransition = currentTime;
        }
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
    if (type == 0) {
        if ((currentTime + 1) < HEAD->timeOfEvent) {
            event *new_event = malloc(sizeof(event));
            // new_event->point1
            new_event->type = 0;
            new_event-> timeOfEvent = currentTime + 1;
            insert_event(new_event);
        }
        return;
    }
	// type 1 means point 1 will hit a wall so next wall collision for 1 must be found
	// this is the same for type 2 only for point 2
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
	// This determines if there will be a transition from in range to out of range (or vice versa)
	// within the time to the next wall hit
    double transition = ttotrans();
    // printf("hello\n");
	// transition <= 0 is infinite time to collision and various other errors
    if (transition < 0) {
        // printf("\n");
        // return;
    } else if (transition ==0) {
        // printf("shfkhasdT: %f\n", transition);

    } else {
		// we only insert events that happen before the next wall hit.
        if (HEAD->timeOfEvent > (transitionPhase.time + currentTime)) {
        // if (1) {
            // printf("%f, %f, c:%f\n", HEAD->timeOfEvent, (timeToTransition + currentTime), currentTime);
            counter2++;
            event *new_event = malloc(sizeof(event));
            new_event->type = 3;
            new_event->valid = true;
            new_event->wall = transitionPhase.phase;
            new_event->timeOfEvent = currentTime + transitionPhase.time;
            // printf("Phase time: %f, next phase: %f\n", transitionPhase.time, new_event->timeOfEvent);
            insert_event(new_event);
        } else {
            counter3++;
            // printf("type: %D in %fs instead of %f\n", HEAD->type, HEAD->timeOfEvent, transitionPhase.time +currentTime);
        }
    }
	// this creates null events to smooth rendering
    if ((currentTime + 1) < HEAD->timeOfEvent && smooth && opengl) {
        event *new_event = malloc(sizeof(event));
        // new_event->point1
        new_event->type = 0;
        new_event-> timeOfEvent = currentTime + 1;
        insert_event(new_event);
    }
}

// math.stackexchange.com/questions/228841/how-do-i-calculate-the-intersections-of-a-straight-line-and-a-circle
// Ax2 + Bx + C = 0 is the equation for the circle of radius centered around the origin
// y = mx + b is the equation for the line that follows the relative velocities and positions
// the problem is the intersection of a line and a circle with the circle radius being the communication
// distance and the line being relative velocities and positions
// the math follows the link above

double ttotrans() {
    double A, B, C, m, b, r, x, y, vx, vy, d, X;
    x = point2->x - point1->x;
    y = point2->y - point1->y;
    vx = point2->vx - point1->vx;
    vy = point2->vy - point1->vy;
    m = vy / vx;
    b = y - (m * x);
    r = RADIUS;
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

    X = (-B - sqrt(d)) / (2 * A);
    double t1 = (X - x) / vx;
    X = (-B + sqrt(d)) / (2 * A);
    double t2 = (X - x) / vx;


    if (t1 < 0.0001 && t2 < 0.0001) {
        return 0;
    } else if (t1 < 0.0001) {
        transitionPhase.time =  t2;
        transitionPhase.phase = 0;
        return 1;
    } else if (t2 < 0.0001) {
        transitionPhase.time =  t1;
        transitionPhase.phase = 0;
        return 1;
    } else if (t1 < t2) {
        transitionPhase.time =  t1;
        transitionPhase.phase = 1;
    } else {
        transitionPhase.time =  t2;
        transitionPhase.phase = 0;
    }
	// if the roots multiplied are negative then 1 is pos and the other is negative. Therefore we are inside.
    if (t1*t2 >= 0.0f) {
        transitionPhase.phase = 1;
        // printf("positive:1\n");
    } else {
        transitionPhase.phase = 0;
        // printf("negative:0\n");
    }

    // printf("phase change________________%f, %d_____________t1:%f, t2:%f\n", transitionPhase.time, transitionPhase.phase, t1, t2);
    return 1;
    if (transitionPhase.time > 0.0001) {
        return 1;
    } else {
        return 0;
    }
}

// inserts events into our priority queue. They are sorted upon insertion so the head is always popped
// this is a singly linked list
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

// items are inserted in sorted order so we can pop the head
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
// statistics prints values to gnuplots buffer
void statistics(double t) {
    statCounter++;
    // local int counter
    // fprintf(f, "%d %f\n", statCounter++, t);
    fprintf(f, "%f\n", t);
}
