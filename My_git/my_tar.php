<?php

$output = "output";
$extension = ".mytar";
$magic = "@MyTar__scriptFDFSDFDCSDSFREWScript@";
$header = array();

if ($argc <= 1) {
	echo "Veuillez entrer au moins un nom de fichier ou de dossier\n";
	exit();
}

create_archive($argv, $header);

function create_archive($argv, $header) {
	$tarbal = fopen($GLOBALS['output'].$GLOBALS['extension'], 'w');
	$count = count($argv);

	if ($count > 1) {
		for ($i = 1; $i < $count; ++$i) {
			if (file_exists($argv[$i])) {
				$filename = $argv[$i];
				list_files($filename, $filename, 0, $tarbal, $header, false);
			}
		}	

		fwrite($tarbal, $GLOBALS['magic']);
		//We reserve enough space to rewrite the header after we got all the informations about the files
		for ($i = 0; $i < strlen(json_encode($header)) * 3; ++$i) {
			fwrite($tarbal, '0');
		}

		for ($i = 1; $i < $count; ++$i) {
			if (file_exists($argv[$i])) {
				$filename = $argv[$i];
				list_files($filename, $filename, 0, $tarbal, $header, true);
			}
		}

		fseek($tarbal, 0);
		fwrite($tarbal, $GLOBALS['magic'].json_encode($header).$GLOBALS['magic']);
	}

	fclose($tarbal);
}


function list_files($dir, $raw_filename, $level, $handler, &$header, $write) {
	if (is_dir($dir) || is_dir($dir."/")) {
		if (substr($dir, -1) == "/") {
			$dir = substr_replace($dir, "", -1);
		}

		if (substr($raw_filename, -1) == "/") {
			$raw_filename = substr_replace($raw_filename, "", -1);
		}

		if ($opened_dir = opendir($dir)){
			$header[$raw_filename] = NULL;
    		while (($filename = readdir($opened_dir)) !== false){
    			if ($filename != "." && $filename != "..") {
    				if (is_dir($dir."/".$filename."/")) {
    					list_files($dir."/".$filename."/", $filename, ++$level, $handler, $header[$raw_filename], $write);
						//list_files($dir."/".$filename."/", $filename, ++$level, $handler, set_directory($dir, $header), $write);
					} else {
						$content = get_file_info($dir."/".$filename);
						$file_info = array();

						$file_info['dir'] = $raw_filename;
						$file_info['size'] = filesize($dir."/".$filename);
						$file_info['offset'] = ftell($handler); 
				
						$header[$raw_filename][$filename] = $file_info;

						if ($write) {
							fwrite($handler, $content);
						}
					}
				}
			}
	    	closedir($opened_dir);
		}
    } else {
		$content = get_file_info($dir.$filename);
  		$file_info = array();

		$file_info['dir'] = $dir == $raw_filename ? "." : $dir;
		$file_info['size'] = filesize($dir);
		$file_info['offset'] = ftell($handler); 

		$header[$raw_filename] = $file_info;

		if ($write) {
			fwrite($handler, $content);
    	}
    }
}

function set_directory($dir, &$header) {
	$directories = explode("/", $dir);

	var_dump($directories);
    $new_header = $header;

    foreach ($directories as $folder) {
    	$new_header[$folder] = NULL;
    	$new_header = $new_header[$folder];
    }

    return $new_header;
}

function display_file_info($filename, $level) {
	for ($i = 0; $i <= $level; ++$i) {
		echo "\t";
	}
	echo $filename."\n";
}

function get_file_info($filename) {
	if (file_exists($filename)) {
		$handler = fopen($filename, 'r');
		$filesize = filesize($filename);

		if (!empty($handler) && $filesize > 0) {
			$content = fread($handler, $filesize);
		}

		fclose($handler);

		return $content;
	}

	return "";
}

?>