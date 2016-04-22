package game;

import graphics.*;
import input.*;
import sound.*;
import sprites.*;
import util.*;




import java.awt.*;
import java.awt.event.KeyEvent;
import java.util.Iterator;

import javax.sound.midi.Sequence;
import javax.sound.midi.Sequencer;
import javax.sound.sampled.AudioFormat;
import javax.swing.InputMap;



public class game_manager extends game_execution{
	 public static void main(String[] args) {
		 	//int i = main_menu.type();
	        
	        if (args.length == 1) {
	        	map_name = args[0];
	        }
	        else  {
	        	map_name = "maps/map1.txt";
	        }
	        new game_manager(2).run();
	    }

	    // uncompressed, 44100Hz, 16-bit, mono, signed, little-endian
	    private static final AudioFormat PLAYBACK_FORMAT =
	        new AudioFormat(44100, 16, 1, true, false);

	    private static final int DRUM_TRACK = 1;

	    public static final float GRAVITY = 0.002f;

	    public static String map_name;
	    private Point pointCache = new Point();
	    private TileMap map;
	    private MidiPlayer midiPlayer;
	    private SoundManager soundManager;
	    private ResourceManager resourceManager;
	    private Sound prizeSound;
	    private Sound boopSound;
	    private Sound shootSound; //shoot.wav
	    private Sound creatureSound; // hit.wav
	    private Sound got_hit; //p_hit.wav
	    private Sound playdies; //p_die.wav
	    private InputManager inputManager;
	    private TileMapRenderer renderer;

	    private GameAction moveLeft;
	    private GameAction moveRight;
	    private GameAction jump;
	    private GameAction exit;
	    private GameAction shoot;
	    private int shoot_count;
	    private boolean shoot_valid;
	    private boolean shot_before;
	    private long shoot_wait;
	    private long prev_shot_time;
	    public static long start_time;
	    private long time_inb;
	    private boolean let_go;
	    private long first_shoot;
	    private boolean player_hit;
	    public int sec_idle;
	    public long idle_start_time;
	    public static boolean is_idle;
	    public int count_bull = 0;
	    public Creature[] fire_list = new Creature[5];
	    public int bull_ind = 0;
	    
	    public static int typeofp;
	    public game_manager(int type){
	    	this.typeofp = type;
	    }


	    public void init() {
	        super.init();
	        shoot_valid = false;
	        let_go = true;
	        shot_before = false;
	        shoot_wait = 1000;
	        prev_shot_time = 0;
	        time_inb = 1001;
	        first_shoot = 0;
	        idle_start_time = 0;
	        
	        // set up input manager
	        initInput();

	        // start resource manager
	        resourceManager = new ResourceManager(
	        screen.getFullScreenWindow().getGraphicsConfiguration(), typeofp);

	        // load resources
	        renderer = new TileMapRenderer();
	        renderer.setBackground(
	            resourceManager.loadImage("background.png"));

	        // load first map
	        map = resourceManager.loadNextMap();

	        // load sounds
	        soundManager = new SoundManager(PLAYBACK_FORMAT);
	        prizeSound = soundManager.getSound("sounds/prize.wav");
	        boopSound = soundManager.getSound("sounds/boop2.wav");
	        shootSound = soundManager.getSound("sounds/shoot.m4a");
	        creatureSound = soundManager.getSound("sounds/hit.m4a");
	        playdies = soundManager.getSound("sounds/p_die.m4a");
	        got_hit = soundManager.getSound("sounds/p_hit.m4a");

	        // start music
	        //midiPlayer = new MidiPlayer();
	        //Sequence sequence =
	            //midiPlayer.getSequence("sounds/music.midi");
	        //midiPlayer.play(sequence, true);
	        //toggleDrumPlayback();
	    }


	    /**
	        Closes any resurces used by the GameManager.
	    */
	    public void stop() {
	        super.stop();
	        midiPlayer.close();
	        soundManager.close();
	    }


	    private void initInput() {
	        moveLeft = new GameAction("moveLeft");
	        moveRight = new GameAction("moveRight");
	        jump = new GameAction("jump",
	            GameAction.DETECT_INITAL_PRESS_ONLY);
	        exit = new GameAction("exit",
	            GameAction.DETECT_INITAL_PRESS_ONLY);
	        shoot = new GameAction("shoot");

	        inputManager = new InputManager(
	            screen.getFullScreenWindow());
	        inputManager.setCursor(InputManager.INVISIBLE_CURSOR);

	        inputManager.mapToKey(moveLeft, KeyEvent.VK_LEFT);
	        inputManager.mapToKey(moveRight, KeyEvent.VK_RIGHT);
	        inputManager.mapToKey(jump, KeyEvent.VK_SPACE);
	        inputManager.mapToKey(exit, KeyEvent.VK_ESCAPE);
	        inputManager.mapToKey(shoot, KeyEvent.VK_S);
	    }


	    private void checkInput(long elapsedTime, long currTime) {

	        if (exit.isPressed()) {
	            stop();
	        }

	        Player player = (Player)map.getPlayer();
	        player.setidle(true);
	        if (player.isAlive()) {
	            float velocityX = 0;
	            if (moveLeft.isPressed()) {
	                velocityX-=player.getMaxSpeed();
	            }
	            if (moveRight.isPressed()) {
	                velocityX+=player.getMaxSpeed();
	            }
	            if (jump.isPressed()) {
	                player.jump(false);
	            }
	            //System.out.println(shoot_wait);
	            if (moveLeft.isPressed() || moveRight.isPressed() || jump.isPressed()) {
	            	player.setidle(false);
	            }
	            
		        if (player.getidle() == true ) {
		        	idle_start_time += elapsedTime;
		        	if (idle_start_time > 1000) {
		        		sec_idle++;
		        		if (player.gethealth() < 40 ) {
		        			player.incrementHealth(5);
		        		}
		        		if (player.gethealth() > 40) {
		        			player.sethealth(40);
		        		}
		        	
		        		idle_start_time = 0;
		        		
		        	}
		        }
		        else {
		        	idle_start_time = 0;
		        }
	        
	            
	            
	            if (shoot.isPressed()) {
	            	//System.out.println("press");
	            	if (shoot_valid && (currTime > first_shoot + 200)){   
	            		shoot_wait = 0;
	            		first_shoot = currTime;
	            		if (shot_before && shoot_count <= 10) { //rapid fire
	            			shoot_count++;
	            			if (shoot_count > 10) {
	            				shoot_valid = false;
	            			}
	            			System.out.println("SHOOT REPEAT");
	            			fire(player);
	            		}
	            		else { //fire once
	            		shot_before = true;
	            		System.out.println("SHOOT ONCE");
	            		fire(player);
	            		}
	            	}
	            }
	           
	            else { // didn't press S 
	            	//System.out.println("didnt press");
	            	shoot_wait += elapsedTime;
	            	first_shoot = 0;
	            	shot_before = false;
	            	shoot_count = 0;
	            	if (shoot_wait > 1000) {
	            		shoot_valid = true;
	            	}
	            	else {
	            		shoot_valid = false;
	            	}	
	            }
	            
	          
	            	
	            
	          
	            
	          
	            player.setVelocityX(velocityX);
	        }

	    }


	    public void draw(Graphics2D g) {
	    	Creature player = (Creature)map.getPlayer();
	        renderer.draw(g, map,
	            screen.getWidth(), screen.getHeight());
	        g.setFont(new Font("Seriff", Font.BOLD, 46));
	        g.setColor(Color.RED);
	        g.drawString("Health: " + player.gethealth(), 50, 100);
	        g.drawString("Score: " + player.get_points(), 400, 100);
	    }


	    /**
	        Gets the current map.
	    */
	    public TileMap getMap() {
	        return map;
	    }


	    /**
	        Turns on/off drum playback in the midi music (track 1).
	    */
	    public void toggleDrumPlayback() {
	        Sequencer sequencer = midiPlayer.getSequencer();
	        if (sequencer != null) {
	            sequencer.setTrackMute(DRUM_TRACK,
	                !sequencer.getTrackMute(DRUM_TRACK));
	        }
	    }

	

	    /**
	        Gets the tile that a Sprites collides with. Only the
	        Sprite's X or Y should be changed, not both. Returns null
	        if no collision is detected.
	    */
	    public Point getTileCollision(Sprite sprite,
	        float newX, float newY)
	    {
	        float fromX = Math.min(sprite.getX(), newX);
	        float fromY = Math.min(sprite.getY(), newY);
	        float toX = Math.max(sprite.getX(), newX);
	        float toY = Math.max(sprite.getY(), newY);

	        // get the tile locations
	        int fromTileX = TileMapRenderer.pixelsToTiles(fromX);
	        int fromTileY = TileMapRenderer.pixelsToTiles(fromY);
	        int toTileX = TileMapRenderer.pixelsToTiles(
	            toX + sprite.getWidth() - 1);
	        int toTileY = TileMapRenderer.pixelsToTiles(
	            toY + sprite.getHeight() - 1);

	        // check each tile for a collision
	        for (int x=fromTileX; x<=toTileX; x++) {
	            for (int y=fromTileY; y<=toTileY; y++) {
	                if (x < 0 || x >= map.getWidth() ||
	                    map.getTile(x, y) != null)
	                {
	                    // collision found, return the tile
	                    pointCache.setLocation(x, y);
	                    return pointCache;
	                }
	            }
	        }

	        // no collision found
	        return null;
	    }


	    /**
	        Checks if two Sprites collide with one another. Returns
	        false if the two Sprites are the same. Returns false if
	        one of the Sprites is a Creature that is not alive.
	    */
	    public boolean isCollision(Sprite s1, Sprite s2) {
	        // if the Sprites are the same, return false
	        if (s1 == s2) {
	            return false;
	        }

	        // if one of the Sprites is a dead Creature, return false
	        if (s1 instanceof Creature && !((Creature)s1).isAlive()) {
	            return false;
	        }
	        if (s2 instanceof Creature && !((Creature)s2).isAlive()) {
	            return false;
	        }

	        // get the pixel location of the Sprites
	        int s1x = Math.round(s1.getX());
	        int s1y = Math.round(s1.getY());
	        int s2x = Math.round(s2.getX());
	        int s2y = Math.round(s2.getY());

	        // check if the two sprites' boundaries intersect
	        return (s1x < s2x + s2.getWidth() &&
	            s2x < s1x + s1.getWidth() &&
	            s1y < s2y + s2.getHeight() &&
	            s2y < s1y + s1.getHeight());
	    }


	    /**
	        Gets the Sprite that collides with the specified Sprite,
	        or null if no Sprite collides with the specified Sprite.
	    */
	    public Sprite getSpriteCollision(Sprite sprite) {

	        // run through the list of Sprites
	        Iterator i = map.getSprites();
	        while (i.hasNext()) {
	            Sprite otherSprite = (Sprite)i.next();
	            if (isCollision(sprite, otherSprite)) {
	                // collision found, return the Sprite
	                return otherSprite;
	            }
	        }

	        // no collision found
	        return null;
	    }
	    public void addbullet(Creature creature, TileMap map, int tileX, int tileY) {
	    	if (ResourceManager.bulletSprite != null) {
	    		Sprite bullet = (Sprite)ResourceManager.bulletSprite.clone();
	    	
	    	System.out.println(creature.getVelocityX());
	    	if (creature.getVelocityX() < 0) {
	    		bullet.setX(creature.getX() - 50);
	    		bullet.setVelocityX(-1f);
	    		bullet.setVelocityY(0);
	    	}
	    	else {
	    		bullet.setX(creature.getX() + 80);
	    		bullet.setVelocityX(1f);
	    		bullet.setVelocityY(0);
	    	}
	    	
	    	bullet.setY(creature.getY() - 5);
	    	bullet.setstart(tileX);
	    	map.addSprite(bullet); 
	    	//ResourceManager.addSprite(map, bullet, tileX, tileY);
	    	}
	    }

	    /**
	        Updates Animation, position, and velocity of all Sprites
	        in the current map.
	    */
	    public void update(long elapsedTime, long currTime) {
	        Creature player = (Creature)map.getPlayer();


	        // player is dead! start map over
	        if (player.getState() == Creature.STATE_DEAD) {
	            map = resourceManager.reloadMap();
	            return;
	        }

	        // get keyboard/mouse input
	        checkInput(elapsedTime,currTime);

	        
	        int current_tile = TileMapRenderer.pixelsToTiles(player.getX());
	        if (current_tile != player.get_prev()) {
	        	player.set_prev(current_tile);
	        	player.incrementHealth(1);
	        }
	        if (player.gethealth() > 40) {
	        	player.sethealth(40);
	        }
	        // update player
	        player.setidle(true);
	        updateCreature(player, elapsedTime);
	        if (player.gethealth() <= 0) {
	        	player.setState(2);
	        	
	        }
	 
	        player.update(elapsedTime);
	       
	        
	        // add bullet
	        if (player.get_bullet()) {
	        	player.set_bullet(false);
	        	System.out.println("ADDING SPRITE");
	        	player.printhealth();
	        	soundManager.play(shootSound);
	        	ResourceManager.addSprite(map,ResourceManager.bulletSprite,TileMapRenderer.pixelsToTiles(player.getX()) + 2,TileMapRenderer.pixelsToTiles(player.getY()));
	        }
	        
	        
	        // update other sprites
	        boolean killed_bug = false;
	        int prev_tile;
	        int ind = 0;
	        
	        Iterator i = map.getSprites();
	        while (i.hasNext()) {
	            Sprite sprite = (Sprite)i.next();
	            if (sprite instanceof Creature) {
	                Creature creature = (Creature)sprite;
	                if (creature.is_up == true) {
	                	fire_list[ind] = creature; 
	                	ind++;
	                	
	                }
	               
	                if (getSpriteCollision(creature) instanceof Bullet) {
	                	creature.setState(2);
	                	killed_bug = true;
	                	player.add_points();
	                }
	                if (creature.getState() == Creature.STATE_DEAD) {
	                	soundManager.play(creatureSound);
	                	System.out.println(creature);
	                	i.remove();
	                }
	                else {
	                    updateCreature(creature, elapsedTime);
	                }
	            }
	            else if (sprite instanceof Bullet) {
	            	
	            	
	            	if (typeofp == 1 && 7 <= sprite.get_tiles()) {
	            		i.remove();
	            	}
	            	else if (typeofp == 2 && 10 <= sprite.get_tiles()) {
	            		i.remove();
	            	}
	            	if (getTileCollision(sprite,sprite.getX(), sprite.getY()) != null) {
	            		//i.remove();
	            		sprite.setY(sprite.getY() + 500);
	            		sprite.setVelocityX(0);
	            	}
	            	if (killed_bug == true) {
	            		if (player.gethealth() <= 40) {
	            			player.incrementHealth(10);
	            		}
	            		if (player.gethealth() > 40) {
	            			player.sethealth(40);
	            		}
	            		//soundManager.play(killsSound);
	            		killed_bug = false;
	            		i.remove();
	            	}
	            }
	            
	            // normal update
	            sprite.update(elapsedTime);
	        }
	        bull_ind++;
	        if (bull_ind == 200) {
	        	bull_ind = 0;
	        
	        for (int i2 = 0; i2 < ind; i2++)
	        {
	        	soundManager.play(shootSound);
	        	addbullet(fire_list[i2],map, TileMapRenderer.pixelsToTiles(fire_list[i2].getX()), TileMapRenderer.pixelsToTiles(fire_list[i2].getY() - 100));
	        }
	        }

	        

	        	
	      
	        
	    }


	    /**
	        Updates the creature, applying gravity for creatures that
	        aren't flying, and checks collisions.
	    */
	    private void updateCreature(Creature creature,
	        long elapsedTime)
	    {

	        // apply gravity
	        if (!creature.isFlying()) {
	            creature.setVelocityY(creature.getVelocityY() +
	                GRAVITY * elapsedTime);
	        }

	        // change x
	        float dx = creature.getVelocityX();
	        float oldX = creature.getX();
	        float newX = oldX + dx * elapsedTime;
	        Point tile =
	            getTileCollision(creature, newX, creature.getY());
	        if (tile == null) {
	            creature.setX(newX);
	        }
	        else {
	            // line up with the tile boundary
	            if (dx > 0) {
	                creature.setX(
	                    TileMapRenderer.tilesToPixels(tile.x) -
	                    creature.getWidth());
	            }
	            else if (dx < 0) {
	                creature.setX(
	                    TileMapRenderer.tilesToPixels(tile.x + 1));
	            }
	            creature.collideHorizontal();
	        }
	        if (creature instanceof Player) {
	            checkPlayerCollision((Player)creature, false);
	        }

	        // change y
	        float dy = creature.getVelocityY();
	        float oldY = creature.getY();
	        float newY = oldY + dy * elapsedTime;
	        tile = getTileCollision(creature, creature.getX(), newY);
	        if (tile == null) {
	            creature.setY(newY);
	        }
	        else {
	            // line up with the tile boundary
	            if (dy > 0) {
	                creature.setY(
	                    TileMapRenderer.tilesToPixels(tile.y) -
	                    creature.getHeight());
	            }
	            else if (dy < 0) {
	                creature.setY(
	                    TileMapRenderer.tilesToPixels(tile.y + 1));
	            }
	            creature.collideVertical();
	        }
	        if (creature instanceof Player) {
	            boolean canKill = (oldY < creature.getY());
	            checkPlayerCollision((Player)creature, canKill);
	        }

	    }


	    /**
	        Checks for Player collision with other Sprites. If
	        canKill is true, collisions with Creatures will kill
	        them.
	    */
	    public void checkPlayerCollision(Player player,
	        boolean canKill)
	    {
	        if (!player.isAlive()) {
	            return;
	        }

	        // check for player collision with other sprites
	        Sprite collisionSprite = getSpriteCollision(player);
	        if (collisionSprite instanceof PowerUp) {
	            acquirePowerUp((PowerUp)collisionSprite, player);
	        }
	        else if (collisionSprite instanceof Creature) {
	            Creature badguy = (Creature)collisionSprite;
	            canKill = false;
	            if (canKill) {
	                // kill the badguy and make player bounce
	                soundManager.play(boopSound);
	                badguy.setState(Creature.STATE_DYING);
	                player.setY(badguy.getY() - player.getHeight());
	                player.jump(true);
	            }
	            else {
	                // player dies!
	            	soundManager.play(playdies);
	                player.setState(Creature.STATE_DYING);
	            }
	        }
	        else if (collisionSprite instanceof Bullet) {
	        	soundManager.play(got_hit);
	        	player.decrementHealth(5);
	        	collisionSprite.setY(collisionSprite.getY() + 1000);
	        }
	    }


	    /**
	        Gives the player the speicifed power up and removes it
	        from the map.
	    */
	    public void acquirePowerUp(PowerUp powerUp, Player player) {
	        // remove it from the map
	        map.removeSprite(powerUp);

	        if (powerUp instanceof PowerUp.Star) {
	            // do something here, like give the player points
	            soundManager.play(prizeSound);
	        }
	        else if (powerUp instanceof PowerUp.Music) {
	            // change the music
	            soundManager.play(prizeSound);
	            toggleDrumPlayback();
	        }
	        else if (powerUp instanceof PowerUp.Goal) {
	            // advance to next map
	            soundManager.play(prizeSound,
	                new EchoFilter(2000, .7f), false);
	            map = resourceManager.loadNextMap();
	        }

	        	
	       
	    }
	    
	    public void fire(Player player) {
	    	player.spawn_bullet = true;
	    }


		public static void setidle(boolean b) {
			// TODO Auto-generated method stub
			is_idle = b;
		}

	}
