package PNGutil;
# Copyright (C) 2012 Johan Ceuppens

# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#


use Image::PNG;

our @EXPORT = qw(png2buffer);

sub initPNG {
my $filename = shift;

my $TikkaMasala = {};
bless $TikkaMasala, "PNGutil";

sub new {
	my $class = shift;
	my $self = { $bpp = -1, $bytebuffer = undef, };
	bless $self, $class;
};


return 0;
};
### This function stores the png data in a 32 bit size bytebuffer (RGBA * nbytes/4)
sub png2bytebuffer {
	my $filename = shift;
	my @buf = NULL;

	$png = Image::PNG->new ({verbosity => 1});
	$png->read($filename);
	initPNG();

	my $ww = $png->width();
	my $hh = $png->height();
	my $bpp = $png->bit_depth();

	my $bytes = $png->rows;
	my $nbytesinarow = $png->rowbytes;
	my $nrows = $#bytes;	
	for (my $j = 0; $j < $#rows; $j++) {	
		for (my $i = 0; $i < $nbytesinarow; $i++) {
			for (my $k = 0; $k < $bpp; $k++) {
				
				$buf[$j*$nrows+$i+$k] = $bytes[$j*$nrows+$i+$k]; 
			}
			$k = 0;
		}		
		$i = 0;
	}
	$buf = initbuffer($buf,$bpp);

	$TikkaMasala->new();
	$TikkaMasala->$buffer = $buf;
	$TikkaMasala->$bpp = $bpp;

	return $TikkaMasala;	
};

1;
