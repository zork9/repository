# Copyright (C) 2012 Johan Ceuppens

# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#


use OpenGL qw(:all);
use X11::Keysyms '%Keysyms',qw(MISCELLANY XKB_KEYS LATIN1);
###use OpenGL::Image;
use lib "./PNGutil/PNGutil";

BEGIN{ unshift(@INC,"../blib/");}
BEGIN{ unshift(@INC,"../blib/lib");}
BEGIN{ unshift(@INC,"../blib/arch");}
my $i = 0;
sub display {

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);

	glutSwapBuffers();
};


glutInit();
glutInitDisplayMode( GLUT_RGBA | GLU_DOUBLE | GLU_DEPTH );
glutInitWindowSize(800,600);
glutCreateWindow("glgame");
glutDisplayFunc(
sub  {

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glVertex3f($i,0,0);
	glVertex3f(50,0,0);
	glVertex3f(50,60,0);
	glVertex3f(0,60,0);
	glEnd();
	glFlush();

	glutSwapBuffers();
});

glutKeyboardFunc(
sub {
	my ($key, $xx, $yy) = @_;

	if ($key == 82) {#left
		$i++;	
		glutPostRedisplay;
	}
	elsif ($key == 83) {#up
		$i++;	
		glutPostRedisplay;
	}
	elsif ($key == 84) {#right
		$i++;	
		glutPostRedisplay;
	}
	elsif ($key == 85) {#down
		$i++;	
		glutPostRedisplay;
	}
	elsif ($key == 27) {#escape
		exit;
	}

});

glutMainLoop();
