package PNGutil;
# Copyright (C) 2012 Johan Ceuppens

# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#


our @EXPORT = qw(seek,position);
my $SEEK_SET = 0;
my $SEEK_CUR = 1;
my $SEEK_END = 2;

my @buffer = NULL;
my $index = NULL;
my $bpp = -1;
sub initbuffer {
	my $b = shift;
	my $bpp0 = shift;

	$bpp = $bpp0;	
	$index = 0;
	if ($b == NULL || $b == "") {
		$buffer = NULL;
		return $buffer;
	} 	
	$buffer = $b;
	return $buffer;
};

sub seek {
	my $offset = shift;
	my $whence = shift;

	if ($whence == $SEEK_SET) {
		position($offset);
	}
	else {
		if  ($whence == $SEEK_CUR) {
			position($offset+$index);
		}
		else { 
			if ($whence == $SEEK_END) {
				position(length($buffer)-$offset);
			}
		}
	}
};
	
sub position {
	my $idx = shift;
	
	$index = $idx;	
	return 0;
};

sub get {
	my $idx = shift;

	return $buffer[$idx];
};

sub set {
	my $idx = shift;
	my $byte = shift;
	if (not defined $byte) { 
		$buffer[$index] = $byte;
	} else {
		$buffer[$idx] = $byte;
	}
};

# get next RGBA bytes
sub getRGBA {
	my @lst = (); 
	for (my $i = 0; $i < $bpp+1; $i++) {
		$lst[$i++] = $buffer[$index++];
	}

	return $lst;
};
 
			
1;
