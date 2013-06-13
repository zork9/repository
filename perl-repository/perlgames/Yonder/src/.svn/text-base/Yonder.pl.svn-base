# Copyright (C) 2012 Johan Ceuppens

# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#


use SDL;
use SDL::Video;
use SDL::Surface;
use SDL::Image;
use SDL::Rect;
use SDLx::App;

use lib './src/';
use Player;
use TileMapLevel1;
use BoundingBox;
use Gateway;


BEGIN{ unshift(@INC,"../blib/");}
BEGIN{ unshift(@INC,"../blib/lib");}
BEGIN{ unshift(@INC,"../blib/arch");}
my $player = Player->new(100,100);
my $tilemap = undef;
my @boundingboxes = ();
my @gateways = ();

sub loadlevel1 {
	$tilemap = TileMapLevel1->new(0,0,320,200);
	$tilemap->addImage("./pics/16tiles-length.png");

	$tilemap->generateLevel1();

##	push(@boundingboxes,BoundingBox->new(0,400,320,20));	
##	$gw = Gateway->new(100,400,320,20,1001);
##	$gw->addImage("./pics/door-48x48-1.png");
##	push(@gateways, $gw);
		
};

my $screenwidth = 320;
my $screenheight = 200;

my $app = SDLx::App->new($screenwidth, $screenheight);

my $playerpngsurface;
$playerpngsurface = \$player->getStaticImage();
my $mappngsurface;


SDL::Image::init(IMG_INIT_PNG);
loadlevel1();

$app->add_show_handler( sub {

	my $mappngsurface = $tilemap->getTilesImage();

	if ( ${${$mappngsurface}} ) {
		foreach ($tilemap->getTileList()) {
			${${mappngsurface}}->blit($app, 
				[$_[1],$_[2],16,16],
				[$tilemap->getx()+$_[3],$tilemap->gety()+$_[4],0,0]);
		}

		$srcrect = SDL::Rect->new(0,0,16,16);
		SDL::Video::update_rects($app,$srcrect);
	}
	if ( $playerpngsurface ) {
		${${$playerpngsurface}}->blit($app, undef, [$player->getx(),$player->gety(),0,0]);
	}


###	SDL::Video::blit_surface(${${${$mappngsurface}}},[0,0,100,100],$app,[100,100,100,100]);
	
	foreach (@gateways) {
		if ($_ and $_->getImage()) {
	###FIXME	${${$_->getImage()}}->blit($app, undef, [$_->getx(),$_->gety(),$_->getw(),$_->geth() ]);
		}
	}	
	foreach (@gateways) {	
		if ( $_->collision($player) ) {
			my $k = $_->getlevelnumber();
			if ($k == 1000) {
				loadlevelnumber1000();
			} elsif ($k == 1001) {
				###loadlevelnumber1001();
			} else {	
			}
			$app->update();
			return;
		}
	}
	foreach (@boundingboxes) {	
		if ( $_->collision($player) ) {
			return;###FIXME
		}
	}
	$app->update();
});

$app->add_event_handler(
sub {
###FIXME	$app->stop();
});

$app->add_event_handler(
sub {
	$app->draw_rect( [ 0,0,$app->w,$app->h],0);	

	my $event = shift;
##	my $event = SDL::Event->new();

###	SDL::Events::pump_events();

###	while (SDL::Events::poll_event($event)) {
	
	
		if ($event->type == SDL_KEYDOWN )
		{
			my $key_name = SDL::Events::get_key_name($event->key_sym);

			$playerpngsurface = \$player->getImage();
			$tilemap->moveright() if $key_name =~ /^j$/ or $app->update();
			$tilemap->moveleft() if $key_name =~ /^l$/ or $app->update();
			$tilemap->movedown() if $key_name =~ /^i$/ or $app->update();
			$tilemap->moveup() if $key_name =~ /^k$/ or $app->update();

		} 
		elsif ($event->type == SDL_KEYUP )
		{
			$playerpngsurface = \$player->getStaticImage();
			my $key_name = SDL::Events::get_key_name($event->key_sym);
			$app->update();
		}
###	}

});

$app->run();

print "Quitting.";
