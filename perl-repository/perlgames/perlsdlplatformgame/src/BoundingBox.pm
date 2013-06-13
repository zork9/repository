# Copyright (C) 2012 Johan Ceuppens

# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#

package BoundingBox;

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
	my $self = { $x => shift, $y => shift, $w => shift, $h = shift, };
	bless $self, $class;
	return $self;
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


sub collision {
	my ($self,$player) = @_;

	my $px = $player->getx();
	my $py = $player->gety();
	my $pw = $player->getw();
	my $ph = $player->geth();

	my $bbx = $self->getx();
	my $bby = $self->gety();
	my $bbw = $self->getw();
	my $bbh = $self->geth();


	if ($px >= $bbx and $px <= $bbx + $bbw and $py >= $bby and $py <= $bby + $bbh) {
		return 1;
	} else {
		return 0;
	}

};

1;

