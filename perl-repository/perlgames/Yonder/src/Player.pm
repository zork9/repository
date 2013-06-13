# Copyright (C) 2012 Johan Ceuppens

# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#

package Player;

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
			$direction => "right",
			$hitpoints => 10, 
			$maxhitpoints => 10, 	

			$leftimages, 
			$rightimages,
			$staticleftimages, 
			$staticrightimages, 
			 };


	bless $self, $class;

	$self->{leftimages} = StateImageLibrary->new(), 
	$self->{rightimages}= StateImageLibrary->new(),
	$self->{staticleftimages} = StateImageLibrary->new(), 
	$self->{staticrightimages} = StateImageLibrary->new(), 

	$self->{staticleftimages}->add("./pics/trex-80x80-left-1.png");
        $self->{staticrightimages}->add("./pics/trex-80x80-right-1.png");

	$self->{leftimages}->add("./pics/trex-80x80-left-1.png");
        $self->{leftimages}->add("./pics/trex-80x80-left-2.png");
        $self->{leftimages}->add("./pics/trex-80x80-left-3.png");
        $self->{leftimages}->add("./pics/trex-80x80-left-4.png");
        $self->{leftimages}->add("./pics/trex-80x80-left-5.png");
        $self->{leftimages}->add("./pics/trex-80x80-left-6.png");
        $self->{leftimages}->add("./pics/trex-80x80-left-7.png");
        $self->{leftimages}->add("./pics/trex-80x80-left-8.png");
        $self->{leftimages}->add("./pics/trex-80x80-left-9.png");

        $self->{rightimages}->add("./pics/trex-80x80-right-1.png");
        $self->{rightimages}->add("./pics/trex-80x80-right-2.png");
        $self->{rightimages}->add("./pics/trex-80x80-right-3.png");
        $self->{rightimages}->add("./pics/trex-80x80-right-4.png");
        $self->{rightimages}->add("./pics/trex-80x80-right-5.png");
        $self->{rightimages}->add("./pics/trex-80x80-right-6.png");
        $self->{rightimages}->add("./pics/trex-80x80-right-7.png");
        $self->{rightimages}->add("./pics/trex-80x80-right-8.png");
        $self->{rightimages}->add("./pics/trex-80x80-right-9.png");


	return $self;
};

sub getStaticImage {
	my ($self) = @_;
	if ($self->{direction} == "left") {
		return $self->{leftimages}->getwithindex(0);
	} elsif ($self->{direction} == "right") {
		return $self->{rightimages}->getwithindex(0);
	} else {###default leftimage
		return $self->{leftimages}->getwithindex(0);
	}
};

sub getImage {
	my ($self) = @_;
	if ($self->{direction} == "left") {
		return $self->{leftimages}->get();
	} elsif ($self->{direction} == "right") {
		return $self->{rightimages}->get();
	} else {###default leftimage
		return $self->{leftimages}->get();
	}
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

sub fall {
	my ($self) = @_;
	$self->{y}++;
}

1;

