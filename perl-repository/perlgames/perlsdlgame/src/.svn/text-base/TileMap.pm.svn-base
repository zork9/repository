# Copyright (C) 2012 Johan Ceuppens

# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#

package TileMap;

use SDL;
use SDL::Video;
use SDL::Surface;
use SDL::Image;
use SDL::Rect;
use SDLx::App;

use lib './src/';
use StateImageLibrary;

BEGIN{ unshift(@INC,"../blib/");}
BEGIN{ unshift(@INC,"../blib/lib");}
BEGIN{ unshift(@INC,"../blib/arch");}

### use addImage after new for setting the tiles gfx
sub new {
	my $class = shift;
	my $self = { 
			$x => shift,
			$y => shift,
			$w => shift,
			$h => shift,
			$tilemap,
			@tilemaptilenumbers = (),
			$tileimages,
			$rgbasurface, 
			 };
	bless $self, $class;

	$self->{tilemaptilenumbers} = (0);
	$self->{tilemap} = StateImageLibrary->new();	
	$self->{tileimages} = StateImageLibrary->new();	
	$self->{rgbasurface} = \SDLx::Surface->new(width=>800,height=>600);

	return $self;
};

sub getImage {
	my ($self) = @_;

	## init map made up of tiles
	my $ww = 16;
	my $i = 0;;
	$self->{tilemap} = StateImageLibrary->new();	
	foreach (@tilemaptilenumbers) {
		if ($_ and $_ == 0) {
			### get tilesheet
			my $surface = $self->{tileimages}->get(); 
			my $surface2 = SDLx::Surface->new( surface => $surface );
			$x = $i % $ww;
			$y = $i / $ww;	
			SDL::Video::blit_surface($surface2,
						[0,0,16,16],
						$self->{rgbasurface},	
						[0,0,$x,$y]);
		}
	
		$i++;
	}
	return \$self->{rgbasurface};
};

sub getTilesImage {
	my ($self) = @_;
	return $self->{tileimages}->get();
};

sub addImage {
	my ($self,$imgfilen) = @_;
	$self->{tileimages}->add($imgfilen);
};

sub getx {
	my ($self) = @_;

	return $self->{x};
};

sub gety {
	my ($self) = @_;

	return $self->{y};
};

sub getw {
	my ($self) = @_;

	return $self->{w};
};

sub geth {
	my ($self) = @_;

	return $self->{h};
};

sub setx {
	my ($self,$xx) = @_;
	$self->{x} = $xx;
}

sub sety {
	my ($self,$yy) = @_;
	$self->{y} = $yy;
}

sub moveleft {
	my ($self) = @_;
	$self->{x}--;
};

sub moveright {
	my ($self) = @_;
	$self->{x}++;
};

sub moveup {
	my ($self) = @_;
	$self->{y}--;
};

sub movedown {
	my ($self) = @_;
	$self->{y}++;
};



1;

