<?
<!--

 Copyright (c) 2012 Johan Ceuppens

 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:
 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
 3. The name of the authors may not be used to endorse or promote products
    derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
-->

echo 'The wizard was questioned about ';
echo $_POST["tully"];
echo '...';
echo '<hr>';

function Strcmpsolo($main_str,$substr)
{
	for ($i = 0; $i < strlen($main_str); $i++) {
		if (substr_compare($main_str,$substr,$i) == 0) {
			return 0;
		}
	}
	return -1;
};

function query_wizard($bar)
{
	$baz = 0;
	if (Strcmpsolo($bar, "caspider") == 0
		||
		Strcmpsolo($bar, "a spider") == 0)
	{
		echo 'I know of a kobold who wanted to become a wizard.';
		echo 'Here is his <a href="./cave-spider/">./cave-spider</a>.';
		echo '<hr>';
		$baz = 1;
	}

	if (Strcmpsolo($bar, "spider") == 0
		||
		Strcmpsolo($bar, "a spider") == 0
                ||
                Strcmpsolo($bar, "cave spider") == 0
                ||
		Strcmpsolo($bar, "a cave spider") == 0
                ||
		Strcmpsolo($bar, "cave-spider") == 0)
	{
		echo 'I know of a kobold who wanted to become a wizard.';
		echo 'Here is his <a href="./cave-spider/">./cave-spider</a>.';
		echo '<hr>';
		$baz = 1;
	}
	if (Strcmpsolo($bar, "encryption") == 0
		||
		Strcmpsolo($bar, "Encryption") == 0
                ||
                Strcmpsolo($bar, "blowfish") == 0)
        {
		echo 'I know of a kobold who wanted to become a wizard.';
		echo 'Here is his <a href="./encryption/">./encryption</a>.';
		echo '<hr>';
		$baz = 1;
	}
	if (Strcmpsolo($bar, "csan") == 0
		||
		Strcmpsolo($bar, "CSAN") == 0
                ||
                Strcmpsolo($bar, "snow") == 0)
        {
		echo 'I know of a kobold who wanted to become a wizard.';
		echo 'Here is his <a href="./CSAN/">./encryption</a>.';
		echo '<hr>';
		$baz = 1;
	}
	if (Strcmpsolo($bar, "snow") == 0
		||
                Strcmpsolo($bar, "Snow") == 0)
        {
		echo 'I know of a kobold who wanted to become a wizard.';
		echo 'Here is his <a href="./snow/">./snow</a>.';
		echo '<hr>';
		$baz = 1;
	}
        if (Strcmpsolo($bar, "scgame") == 0
		||
                Strcmpsolo($bar, "SCgame") == 0)
        {
		echo 'I know of a kobold who wanted to become a wizard.';
		echo 'Here is his <a href="./scgame/">./scgame</a>.';
		echo '<hr>';
		$baz = 1;
	}
        if (Strcmpsolo($bar, "scganadu") == 0
		||
                Strcmpsolo($bar, "SCganadu") == 0)
        {
		echo 'I know of a kobold who wanted to become a wizard.';
		echo 'Here is his <a href="./scganadu/">./scganadu</a>.';
		echo '<hr>';
		$baz = 1;
	}
        if (Strcmpsolo($bar, "schemedoc") == 0
		||
                Strcmpsolo($bar, "Schemedoc") == 0)
        {
		echo 'I know of a kobold who wanted to become a wizard.';
		echo 'Here is his <a href="./schemedoc/">./schemedoc</a>.';
		echo '<hr>';
		$baz = 1;
	}
        if (Strcmpsolo($bar, "thttpd") == 0
		||
                Strcmpsolo($bar, "http") == 0)
        {
		echo 'I know of a kobold who wanted to become a wizard.';
		echo 'Here is his <a href="./thttpd/">./thttpd</a>.';
		echo '<hr>';
		$baz = 1;
	}
        if (Strcmpsolo($bar, "tmail") == 0
		||
                Strcmpsolo($bar, "Tmail") == 0)
        {
		echo 'I know of a kobold who wanted to become a wizard.';
		echo 'Here is his <a href="./tmail/">./tmail</a>.';
		echo '<hr>';
		$baz = 1;
	}
        if (Strcmpsolo($bar, "27tree") == 0
		||
                Strcmpsolo($bar, "twentyseventree") == 0)
        {
		echo 'I know of a kobold who wanted to become a wizard.';
		echo 'Here is his <a href="./twentyseventree/">./twentyseventree</a>.';
		echo '<hr>';
		$baz = 1;
	}

	if (Strcmpsolo($bar, "gnome") == 0
		||
		Strcmpsolo($bar, "a gnome") == 0)
	{
		echo 'I know of a gnome who quested much and many a quest.';    		echo '<hr>';
		$baz = 1;
	}
	if (Strcmpsolo($bar, "3d") == 0
		||
		Strcmpsolo($bar, "a 3d engine") == 0
		||
		Strcmpsolo($bar, "engine") == 0)
	{
		echo 'I know of magical tools which can aid you in your life of
		echo '<hr>';
		$baz = 1;
	}
	if (Strcmpsolo($bar, "tux") == 0
		||
		Strcmpsolo($bar, "megatux") == 0
		||
		Strcmpsolo($bar, "penguin") == 0
		||
		Strcmpsolo($bar, "megaman") == 0)
	{
		echo 'There was once a penguinoid.';
		echo '<hr>';
		$baz = 1;
	}
	else
	{

		echo 'I knowest not.';
		echo '<hr>';

	}
};

query_wizard($_POST["tully"]);
echo '</body></html>';
?>
