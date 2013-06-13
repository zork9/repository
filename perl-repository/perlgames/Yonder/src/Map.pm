# Copyright (C) 2012 Johan Ceuppens

# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#

package Map;

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

sub new {
	my $class = shift;
	my $self = { 
			$x => shift,
			$y => shift,
			$w => shift,
			$h => shift,
			$images, 
			 };
	bless $self, $class;

	$self->{images} = StateImageLibrary->new();
	return $self;
};

sub addImage {
	my ($self,$imgfilen) = @_;
	$self->{images}->add($imgfilen);
};

sub getImage {
	my ($self) = @_;
	return $self->{images}->get();
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
1;

