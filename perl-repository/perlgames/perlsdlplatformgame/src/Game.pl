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
use Map;
use BoundingBox;
use Gateway;


BEGIN{ unshift(@INC,"../blib/");}
BEGIN{ unshift(@INC,"../blib/lib");}
BEGIN{ unshift(@INC,"../blib/arch");}
my $player = Player->new(100,100);
my $map = undef;
my @boundingboxes = ();
my @gateways = ();

sub loadlevel1000 {
	$map = Map->new(0,0,800,600);
	$map->addImage("./pics/door-48x48-1.png");
	$mappngsurface = $map->getImage();
	push(@boundingboxes,BoundingBox->new(0,400,800,20));	
	$gw = Gateway->new(100,400,800,20,1001);
	$gw->addImage("./pics/door-48x48-1.png");
	push(@gateways, $gw);
		
};

my $screenwidth = 800;
my $screenheight = 600;

my $app = SDLx::App->new($screenwidth, $screenheight);

my $playerpngsurface;
$playerpngsurface = $player->getStaticImage();
my $mappngsurface;


SDL::Image::init(IMG_INIT_PNG);
loadlevel1000();

$app->add_show_handler( sub {
	if ( $playerpngsurface ) {
		$playerpngsurface->blit($app, undef, [$player->getx(),$player->gety(),0,0]);
	}	
	if ( $mappngsurface ) {
		$mappngsurface->blit($app, undef, [$map->getx(),$map->gety(),$map->getw(),$map->geth() ]);
	}
	foreach (@gateways) {
		$_->getImage()->blit($app, undef, [$_->getx(),$_->gety(),$_->getw(),$_->geth() ]);
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
	$player->fall();
	$app->update();
});

$app->add_event_handler(
sub {
###FIXME	$app->stop();
});

$app->add_event_handler(
sub {
	my $event = shift;

	$app->draw_rect( [ 0,0,$app->w,$app->h],0);	

	if ($event->type == SDL_KEYDOWN )
	{
		my $key_name = SDL::Events::get_key_name($event->key_sym);

		$playerpngsurface = $player->getImage();
		$player->moveleft() if $key_name =~ /^j$/;
		$player->moveright() if $key_name =~ /^l$/;

	} 
	elsif ($event->type == SDL_KEYUP )
	{
		$playerpngsurface = $player->getStaticImage();
		my $key_name = SDL::Events::get_key_name($event->key_sym);
	}
	$app->update();

});

$app->run();

print "Quitting.";
