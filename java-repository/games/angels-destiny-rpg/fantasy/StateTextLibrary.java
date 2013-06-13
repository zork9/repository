package fantasy;
/*
Copyright (C) <year> <name of author>

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

class StateTextLibrary
{

private LinkedList texts = new LinkedList();//FIXME static array size
String prefix = "./pics/";

private int index;
private int max;

public StateTextLibrary()
{
	index = 0;
	max = 0;
}
public void addText(String text)
{
      texts.add(text);
      max += 1;     	
}
public String getText()
{
      if (index >= max)
	index = 0;
      Object s = texts.get(index++);
      return (String)s;
}
public String getText(int idx)
{
//      if (idx >= max || idx < 0)
//	return "None";

      Object s = texts.get(idx);
      return (String)s;
}

public void setText(int idx, String s)
{
      if (idx >= max || idx < 0)
	return;

	texts.set(idx, s);
}

public int getmax()
{
	return max;
}

public int getindex()
{
	return index;
}
};
