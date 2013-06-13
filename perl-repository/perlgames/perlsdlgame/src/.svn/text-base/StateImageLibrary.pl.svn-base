# Copyright (C) 2012 Johan Ceuppens

# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#

package StateImageLibrary;

use SDL;
use SDL::Video;
use SDL::Surface;
use SDL::Image;
use SDL::Rect;
use SDLx::App;

BEGIN{ unshift(@INC,"../blib/");}
BEGIN{ unshift(@INC,"../blib/lib");}
BEGIN{ unshift(@INC,"../blib/arch");}

sub new {
	my $class = shift;
	my $self = { $index = 0, @images = undef, };
	bless $self, $class;
	return $self;
};

sub add {
	my ($self, $imagefn) = @_;
	my $pngsurface = SDL::Image::load("./pics/test.png");
	my $surface = SDLx::Surface->new( surface => $pngsurface);	
	$self->{images}[$self->index++] = $surface; 
};	

sub addImage {
	add(shift);
};

sub get {
	my $self = shift;
	if ($self->index >= $#images) {
		$self->index = 0;
	}
	return $self->{image}[$self->index++];	
};


1;
