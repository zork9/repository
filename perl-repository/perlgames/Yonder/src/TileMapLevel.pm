# Copyright (C) 2012 Johan Ceuppens

# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#

package TileMapLevel;

use SDL;
use SDL::Video;
use SDL::Surface;
use SDL::Image;
use SDL::Rect;
use SDLx::App;

use lib './src/';
use StateImageLibrary;
use TileMapWithNumbers;

BEGIN{ unshift(@INC,"../blib/");}
BEGIN{ unshift(@INC,"../blib/lib");}
BEGIN{ unshift(@INC,"../blib/arch");}

our @ISA = qw(TileMapWithNumbers);

my $screenwidth = 320;
my $screenheight = 200;
my $tilewidth = my $tileheight = 16;

### use addImage after new for setting the tiles gfx
sub new {
	my $class = shift;
	my $self = $class->SUPER::new($x => shift, $y => shift, $w => shift, $h = shift);
	bless $self, $class;
	return $self;
};

###
### Yonder map 
###

sub generatemaptileempty {

### [ 1st : tilenumber 2nd : Surface srcx 3rd : srcy 4th : destx 5th : desty ]

	my ($self,$l) = @_;
	push(@{$l},0);## maptile 0 at 0,0 in sheet
	push(@{$l},0);
	push(@{$l},0);
};

1;

