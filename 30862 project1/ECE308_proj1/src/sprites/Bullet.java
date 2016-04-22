package sprites;
import java.lang.reflect.Constructor;

import graphics.*;

public class Bullet extends Sprite {
	public int tiles_moved;
	public int start_tile;
	public int current_tile;
	public int spawned_by;
	public int type;
	
	public Bullet(Animation anim) {
		super(anim);
		setVelocityY(0);
		setVelocityX(1f);
		tiles_moved = 0;
		spawned_by = 1;
		
	}
	
    public Object clone() {
        // use reflection to create the correct subclass
        Constructor constructor = getClass().getConstructors()[0];
        try {
            return constructor.newInstance(
                new Object[] {(Animation)anim.clone()});
        }
        catch (Exception ex) {
            // should never happen
            ex.printStackTrace();
            return null;
        }
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
  
    
    }
    
  
	
	
