package sprites;

import game.game_manager;
import graphics.Animation;

/**
    The Player.
*/
public class Player extends Creature {

    private static final float JUMP_SPEED = -.95f;
    public int health;
    public int score;
    public int tiles_moved;
    public int start_tile;
    public int current_tile;
    public boolean spawn_bullet;
    private boolean onGround;
    private boolean is_idle;
    public Player(Animation left, Animation right,
        Animation deadLeft, Animation deadRight)
    {
        super(left, right, deadLeft, deadRight);
        health = 20;
        spawn_bullet = false;
        is_idle = true;
        score = 0;
        
    }


    public void collideHorizontal() {
        setVelocityX(0);
    }


    public void collideVertical() {
        // check if collided with ground
        if (getVelocityY() > 0) {
            onGround = true;
        }
        setVelocityY(0);
    }


    public void setY(float y) {
        // check if falling
        if (Math.round(y) > Math.round(getY())) {
            onGround = false;
        }
        super.setY(y);
    }


    public void wakeUp() {
        // do nothing
    }


    /**
        Makes the player jump if the player is on the ground or
        if forceJump is true.
    */
    public void jump(boolean forceJump) {
        if (onGround || forceJump) {
            onGround = false;
            setVelocityY(JUMP_SPEED);
        }
    }


    public float getMaxSpeed() {
        if (game_manager.typeofp == 1) {
        	return (0.55f); }
        else {
        	return (0.4f);
        }
    }
    
    public void decrementHealth(int amount) {
    	health -= amount;
    }
    
    public void incrementHealth(int amount) {
    	health += amount;
    }
    public boolean get_bullet() {
    	return spawn_bullet;
    }
    
    public void set_bullet(boolean value)
    {
    	spawn_bullet = value;
    }
    public void printhealth()
    {
    	System.out.println(health);
    }
    public int gethealth()
    {
    	return health;
    }
    public void sethealth(int amount)
    {
    	health = amount;
    }
    public boolean getidle() {
    	return is_idle;
    }
    public void setidle(boolean value) {
    	is_idle = value;
    }
    public int get_tiles() {
    	return tiles_moved;
    }
    
    public void increment_tiles()
    {
    	tiles_moved++;
    }
    
    public void setstart(int tile) {
    	current_tile = tile;
    }
    
    public int get_prev()
    {
    	return current_tile;
    }
    
    public void set_prev(int tile)
    {
    	current_tile = tile;
    }
    public void add_points() {
    	score++;
    }
    public int get_points() {
    	return score;
    }
    
    

}
