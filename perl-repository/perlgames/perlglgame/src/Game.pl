# Copyright (C) 2012 Johan Ceuppens

# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#


use OpenGL;
use lib "./PNGutil/PNGutil";

BEGIN{ unshift(@INC,"../blib/");}
BEGIN{ unshift(@INC,"../blib/lib");}
BEGIN{ unshift(@INC,"../blib/arch");}

glpOpenWindow( width => 800, height => 600,
		attributes => [ GLX_RGBA , GLX_DOUBLEBUFFER],
		mask => (MotionNotifyMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask | ExposureMask | InputOutputMask | KeyMapStateMask | ButtonPressMask | ButtonReleaseMask) ) ;
$eventHandler{&ConfigureNotify} = 
	sub {
		my ($event, $width, $height) = @_;
		print "Resizing Viewport to $width and $height\n";
		glViewport( 0,0,$width,$height);
	};

$eventHandler{&ButtonPress} = 
	sub {
		print "pressed mouse button\n";
	};

$eventHandler{&KeyPress} = 
	sub {
		print "pressed key\n";
	};

$eventHandler{&MapNotify} = 
	sub {
		print "map window\n";
	};

$eventHandler{&Expose} = 
	sub {
		print "expose window\n";
	};

$eventHandler{&MotionNotify} = 
	sub {
		print "mouse motion\n";
	};


glClearColor(0,0,1,1);
glClear(GL_COLOR_BUFFER_BIT);
glLoadIdentity;
###glOrtho(-1,1,-1,1,-1,1);


$light_diffuse = pack("f4",1.0,1.0,1.0,1.0);
glLightfv(GL_LIGHT0, GL_DIFFUSE, $light_diffuse);
glLightfv(GL_LIGHT0, GL_AMBIENT, pack("f4",0.0,0.0,0.0,1.0));

my $i = 0;
glColor3f(0,1,0);

sub keyboard {
	my $key = shift;
		if ($key == 27) {
			exit;
		}
		if ($key == '1') {
			$i++;	
		}
};

print "hit CTRL-C to quit\n";
while( 1 ) {
while( $pendingEvent = XPending )
{

	
	my $event = &glpXNextEvent;

	if ( $s = $eventHandler{$event[0]} ) {

		&$s(@event);
	}	

	

glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_POLYGON);
	glVertex3f($i,0,0);
	glVertex3f(50,0,0);
	glVertex3f(50,60,0);
	glVertex3f(0,60,0);
glEnd();
glFlush();
$i+=0.001;
}
}
