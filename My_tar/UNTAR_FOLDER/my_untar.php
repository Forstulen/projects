<?php

$extension = ".mytar";
$magic = "@MyTar__scriptFDFSDFDCSDSFREWScript@";

if ($argc <= 1) {
	echo "Veuillez entrer au moins un nom d'archive\n";
	exit();
}

read_tarbals($argv);


function read_tarbals($argv) {
	$count = count($argv);

	if ($count > 1) {
		for ($i = 1; $i < $count; ++$i) {
			if (file_exists($argv[$i])) {
				$filename = $argv[$i];
				read_header($filename);
			}
		}	
	}
}

function read_header($filename) {
	$file = fopen($filename, 'r');

	$content = fread($file, filesize($filename));

	$header = get_inner_substring($content, $GLOBALS['magic']);

	if (!empty($header)) {
		$tree = json_decode($header, true);
		
		create_files($tree, ".", $content);
	}

	fclose($file);
}

function create_files($tree, $dir, $content) {
	foreach (array_keys($tree) as $key) {
		if (array_key_exists("dir", $tree[$key])) {
			create_file($key, $tree[$key], $dir, $content);
		} else {
			create_directory($dir."/".$key);
			create_files($tree[$key], $dir == "." ? $key : $dir."/".$key, $content);
		}
	}
}

function create_file($filename, $obj, $dir, $content) {
	$size = $obj['size'];
	$offset = $obj['offset'];
			
	$file = fopen($dir."/".$filename, 'w');
	fwrite($file, substr($content, $offset, $size));
	fclose($file);
}

function create_directory($directory) {
	mkdir($directory);
}

function get_inner_substring($string, $delim){
    $string = explode($delim, $string, 3);
    return isset($string[1]) ? $string[1] : '';
}

?>