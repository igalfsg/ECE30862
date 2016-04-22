This is Zork
by: Jeff Heath and Dharna Pahuja

Put an xml file into the main directory using the proper format. 
Using bash and terminal enter: g++ main.cpp Item.cpp Container.cpp Creature.cpp Room.cpp attack.cpp Triggers.cpp 

Run the resulting a.out file.

HOW TO PLAY:

Zork is a text based adventure game that requires skill and thought provoking puzzles. 



Game Commands

    n, s, e, w – movement commands to put the player in a different room. If the indicated direction leads to a new room, the description of the new room is be printed to the screen. Otherwise print “Can’t go that way.”
    i – short for “inventory”, lists all items in the player’s inventory with each item separated by commas, if the player has more than one item. If there are no items in the player's inventory print "Inventory: empty"
    take (item) – changes item ownership from room or container to inventory. If successful print “Item (item) added to inventory”. Hint: “take” can be written as a shortcut for the “put” command)
    open (container) – prints contents of container in format “(container) contains (item), (item), …” and makes those items available to pick up. If empty, you should output "(container) is empty."
    open exit – if the room is of type exit prints “Game Over” and gracefully ends the program.
    read (item) – prints whatever is written on an object that the player has, if something is written on the object and prints “Nothing written.” if nothing is written on the object. If the object is not in the players inventory indicate that by printing an appropriate message.
    drop (item) – changes item ownership from inventory to present room and prints “(item) dropped.”

    If the object is not in the players inventory indicate that by printing an appropriate message.
    put (item) in (container) – adds the item to the containers inventory and and prints “Item (item) added to (container).” If the object is not in the players inventory indicate that by printing an appropriate message.
    turn on (item) – activates an item if it is in the player’s inventory printing “You activate the (item).” and executing commands in the “turnon” element. If the object is not in the players inventory indicate that by printing an appropriate message.
    >attack (creature) with (item) – prints “You assault the (creature) with the (item).” and executes “attack” elements if item matches creature’s “vulnerability” and existing conditions are met. If the object is not in the players inventory indicate that by printing an appropriate message. 



