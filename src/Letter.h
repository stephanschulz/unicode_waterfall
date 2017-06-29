#pragma once

#include "ofMain.h"
#include "grid.h"
#include "Collidable.h"

class Letter : public Collidable
{
public:
    Letter(float x,
        float y,
        float radius,
        Letter * letter_to_my_left,
        char character,
        ofTrueTypeFont * font,
        Grid * grid);
    ~Letter();

    // -- Public Interface.
    void update(float dt);
    void draw();
    bool isDead();

    void kill();

public:
    float getX();
    float getY();


// Init functions
private:

    void init_texture(char character, ofTrueTypeFont * font);


private:
    bool dead = false;
    enum State{WATERFALL, POOL, TEXT_SCROLL};
    State state = WATERFALL;

    bool collision_detection; // Controls whether the letter needs to avoid letters and obstacles.

    char character;
    ofFbo fbo;
    ofFloatColor background_color = ofFloatColor(1.0, 1.0, 1.0);

    ofTrueTypeFont * font;

    // Indicates the letter to the left of this one in the final sentance that will be displayed.
    Letter * letter_to_my_left = NULL;

    // my x = letter_to_my_left x + width + spacing + kerning.
    // my x = left x + x_offset_from_left
    float x_offset_from_left;
    
    float radius;

    // Angle the letter texture is rotated.
    float angle = 0;
    

    // -- Physics dynamics.
    float px, py;
    float vx, vy;
    float ax, ay;

    // The y - coordinate that letters transition from the waterfall behavior to the pooling behavior.
    // define horizontal lines the separate Stage 1, Stage 2, and Stage 3.
    float pool_y_coordinate = 400;
    float text_scroll_y_coordinate = 600;

    // -- Routing functions that call sub behavior functions based on 
    void stepAcceleration(float dt);
    void stepVelocity(float dt);
    void stepPosition(float dt);

    // -- Integration based Physics calculations.
    void dynamicsA(float dt);
    void dynamicsV(float dt);
    void dynamicsP(float dt);

    // -- Waterfall behaviour.
    void stepWaterfallA(float dt);
    void stepWaterfallV(float dt);
    void stepWaterfallP(float dt);

    float gravity = 30;// pixels / time / time.
    float terminal_velocity = 80;


    // -- Pool behavior.
    void stepPoolA(float dt);
    void stepPoolV(float dt);
    void stepPoolP(float dt);

    float pool_y_speed = 30;

    // Text Scroll behaviour.
    void stepTextScrollA(float dt);
    void stepTextScrollV(float dt);
    void stepTextScrollP(float dt);

    float text_scroll_speed = 40;


// Collision Detetion Functions.
private:
    Grid * grid;

// Methods inherited from Collidable.
public:
    virtual bool detect_collision_with_rectangle(ofRectangle rect);

    // Returns true iff this collidable is capable of movement.
    virtual bool isDynamic();

    // Updates this object's internal physics values to point.
    // it away from the direction of collision.
    // Does not modify the position or orientation of the letter, because the letter still needs to validly rmeove itself from the collision grid.
    virtual bool resolve_collision(ofVec3f direction);

    virtual ofRectangle getBoundingBox();

};

