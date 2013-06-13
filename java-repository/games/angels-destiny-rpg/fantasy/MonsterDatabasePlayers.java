package fantasy;
/*
Copyright (C) 2012 Johan Ceuppens

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import javax.swing.ImageIcon;
import java.awt.Toolkit;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import java.util.*;

/*
 */

class MonsterDatabasePlayers extends MonsterDatabase
{

public MonsterDatabasePlayers()
{
	super();


	//add first player character "Anita" 
	monsternames.add("Anita");
	monsterhitpoints.add("45");	
	monstermaxhitpoints.add("45");	
	monsterstrengths.add("10");
	monsterdexterities.add("10");
	monsterintelligences.add("14");
	monsterconstitutions.add("10");
	monsterhitchances.add("12");

	//add second player character "" 
	monsternames.add("Bea");
	monsterhitpoints.add("53");	
	monstermaxhitpoints.add("53");	
	monsterstrengths.add("12");
	monsterdexterities.add("12");
	monsterintelligences.add("13");
	monsterconstitutions.add("12");
	monsterhitchances.add("20");

	//add third player character "" 
	monsternames.add("Bongo");
	monsterhitpoints.add("71");	
	monstermaxhitpoints.add("71");	
	monsterstrengths.add("14");
	monsterdexterities.add("11");
	monsterintelligences.add("16");
	monsterconstitutions.add("14");
	monsterhitchances.add("26");

}

};
