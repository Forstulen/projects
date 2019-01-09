<?php
    
    //Disable warnings
    //error_reporting(0);
    
    //Program
    
    $git = new MyGit();
    
    return $git->launch($argv);
    
    //Class
    
    class MyGit {
        private $commands;
        private $nothing_added = TRUE;
        private $files;

        const PARENT_FOLDER	        =	".MyGitLight";
        const COMMIT_FOLDER         =   ".Commits";
        const COMMIT_FILE           =   ".log";
        const FOLDER_PATH           =   "/.MyGitLight/";
        
        const NO_ARGS               =   "No args";
        const MISSING_PARAMETERS    =   "Missing parameters";
        const NO_FOLDER             =   "could not access";
        const BAD_PERMISSIONS       =   "could not access folder : bad permissions";
        const FOLDER_EXISTS         =   "this folder already has a MyGitLight";
        const NOT_GIT_FOLDER        =   "this folder is not a valid MyGitLight folder";
        const NOTHING_TO_ADD        =   "nothing to add";
        const NOT_EXISTS	        =   "File not found";
        const MISSING_MESSAGE       =   "A commit message is needed";
        const NO_COMMITS            =   "Nothing is commited";
        const REMOVE                =   "rm ";
        const OK                    =   " ok";
        
        const STATUS_MODIFIED       =   "modified :";
        const STATUS_UNTRACKED      =   "untracked :";
        const STATUS_DELETED        =   "deleted :";
        
        public function __construct() {
            $this->$commands = array("init"     =>  1,
                                     "add"      =>  -1,
                                     "rm"       =>  -1,
                                     "commit"   =>  -1,
                                     "log"      =>  0,
                                     "status"   =>  0);
        }
        
        public function launch($args) {
            if (count($args) < 2) {
                echo self::NO_ARGS;
                return -1;
            }
            
            foreach (array_keys($this->$commands) as $key) {
                if ($key == $args[1]) {
                    return $this->$key($args);
                }
            }
        }
        
        private function display_message($error, $message, $arg = "") {
            if ($arg != "") {
                echo $message." ".$arg."\n";
            } else {
                echo $message."\n";
            }
            
            if ($error) {
                return -1;
            }
            return 0;
        }
        
        //STEP1
        private function init($args) {
            if (count($args) < 3) {
                return $this->display_message(TRUE, self::MISSING_PARAMETERS);
            }
            
            $folder = $args[2];
            
            if (is_dir($folder)) {
                if (is_dir($folder.self::FOLDER_PATH)) {
                    return $this->display_message(TRUE, self::FOLDER_EXISTS);
                } else if (mkdir($folder.self::FOLDER_PATH)) {
                    if (!copy(basename($_SERVER['PHP_SELF']), $folder.self::FOLDER_PATH.basename($_SERVER['PHP_SELF']))) {
                        return $this->display_message(TRUE, self::BAD_PERMISSIONS);
                    }
                } else {
                    return $this->display_message(TRUE, self::BAD_PERMISSIONS);
                }
            } else {
                return $this->display_message(TRUE, self::NO_FOLDER, $folder);
            }
            
            return 0;
        }
        
        //STEP2
        private function is_authorized() {
            if (basename(dirname(__FILE__)) === self::PARENT_FOLDER) {
	       return TRUE;
	    }
	    return FALSE;
        }
        
        private function add($args) {
            if ($this->is_authorized() === TRUE) {
	       if (count($args) <= 2) {
	       	  if(!is_dir(dirname(__FILE__)."/".basename(dirname(dirname(__FILE__))))) {
	       	      if (!mkdir(dirname(__FILE__)."/".basename(dirname(dirname(__FILE__))))) {
		      	 return $this->display_message(FALSE, self::BAD_PERMISSIONS);
		      }
		  }
		  if ($this->copy_folder("./", dirname(__FILE__)."/".basename(dirname(dirname(__FILE__))))) {
		     return $this->display_message(TRUE, self::NOTHING_TO_ADD);
		  }
	       } else {
	       	 return $this->analyze_add_arguments($args);
	       }
	    } else {
	       return $this->display_message(TRUE, self::NOT_GIT_FOLDER);
	    }
            
            return 0;
        }

	private function analyze_add_arguments($args) {
		for ($i = 2; $i < count($args); ++$i) {
		    if (!is_dir($args[$i])) {
		       if (file_exists($args[$i])) {
                   $this->copy_file($args[$i], dirname(__FILE__)."/".basename(dirname(dirname(__FILE__)))."/".$args[$i]);
                   continue;
               } else {
                   $this->display_message(TRUE, self::NOT_EXISTS, $args[$i]);
               }
		    } else {
 	       	      if (mkdir(dirname(__FILE__)."/".basename(dirname(dirname(__FILE__)))."/".$args[$i])) {
		      	 $this->copy_folder($args[$i], dirname(__FILE__)."/".basename(dirname(dirname(__FILE__)))."/".$args[$i]);
		      } else {
		      	 return $this->display_message(FALSE, self::BAD_PERMISSIONS);
		      }
		    }
		}
		if ($this->$nothing_added) {
		   return $this->display_message(TRUE, self::NOTHING_TO_ADD);
		}
		return 0;
	}

	private function copy_file($file, $dest_file) {
		if (!file_exists($dest_file) || $this->compare_files($file, $dest_file)) {
		   if (copy($file, $dest_file)) {
               $this->$nothing_added = FALSE;
               return TRUE;
		   }
		}
		return FALSE;
	}
        
    private function compare_files($file, $dest_file) {
        $mdate = date("YmdH:i:s", filemtime($file));
        $date  = date("YmdH:i:s", filemtime($dest_file));
            if ($mdate > $date) {
                return TRUE;
            }
        return FALSE;
    }

	private function copy_folder($dir, $dest_folder) {
		if (basename($dir) !== self::PARENT_FOLDER && $opened_dir = opendir($dir)) {
    		   while (($filename = readdir($opened_dir)) !== false) {
    			if ($filename != "." && $filename != ".." && basename($dir) !== self::PARENT_FOLDER) {
    				if (is_dir($dir."/".$filename."/")) {
				   if (!is_dir($dest_folder."/".$filename)) {
				      $this->$nothing_added = FALSE;
		   		      mkdir($dest_folder."/".$filename);
				   }
    				   $this->copy_folder($dir."/".$filename, $dest_folder."/".$filename);
				} else {
				  if ($this->copy_file($dir."/".$filename, $dest_folder."/".$filename)) {
				     $this->$nothing_added = FALSE;
				  }
				}
			}
		   }
		   closedir($opened_dir);
		}

		return $this->$nothing_added;
	}
 
        private function analyze_rm_arguments($args) {
                for ($i = 2; $i < count($args); ++$i) {
                    if (!is_dir($args[$i])) {
                       if (file_exists($args[$i]) && file_exists(dirname(__FILE__)."/".basename(dirname(dirname(__FILE__)))."/".$args[$i])) {
                           unlink($args[$i]);
                           unlink(dirname(__FILE__)."/".basename(dirname(dirname(__FILE__)))."/".$args[$i]);
                           $this->display_message(TRUE, self::REMOVE.$args[$i].self::OK);
                       } else {
                           $this->display_message(TRUE, self::NOT_EXISTS);
                       }
                    } else if (is_dir(dirname(__FILE__)."/".basename(dirname(dirname(__FILE__)))."/".$args[$i])) {
                        $this->remove_dir($args[$i]);
                        $this->remove_dir(dirname(__FILE__)."/".basename(dirname(dirname(__FILE__)))."/".$args[$i]);
                        $this->display_message(TRUE, self::REMOVE.$args[$i].self::OK);
                    } else {
                        $this->display_message(TRUE, self::NOT_EXISTS);
                    }
                }
                return 0;
        }
        
        private function remove_dir($dir) {
            if (is_dir($dir)) {
                $objects = scandir($dir);
                foreach ($objects as $object) {
                    if ($object != "." && $object != "..") {
                        if (filetype($dir."/".$object) == "dir"){
                            $this->remove_dir($dir."/".$object);
                        }else{
                            unlink($dir."/".$object);
                        }
                    }
                }
                reset($objects);
                rmdir($dir);
            }
        }
        
        private function rm($args) {
            if ($this->is_authorized() === TRUE) {
               if (count($args) > 2) {
                 return $this->analyze_rm_arguments($args);
               } else {
	       	 return $this->display_message(FALSE, self::MISSING_PARAMETERS);
	       }
            } else {
               return $this->display_message(TRUE, self::NOT_GIT_FOLDER);
            }

            return 0;
        }
        
        private function commit($args) {
            if ($this->is_authorized() === TRUE) {
                if (count($args) > 2) {
                    if(!is_dir(dirname(__FILE__)."/".self::COMMIT_FOLDER)) {
                        if (!mkdir(dirname(__FILE__)."/".self::COMMIT_FOLDER)) {
                            return $this->display_message(FALSE, self::BAD_PERMISSIONS);
                        }
                    }
                    
                    $file = NULL;
                    $ID = 1;
                    
                    if(!file_exists(dirname(__FILE__)."/".self::COMMIT_FOLDER."/".self::COMMIT_FILE)) {
                        if ($file = fopen(dirname(__FILE__)."/".self::COMMIT_FOLDER."/".self::COMMIT_FILE, "w+")) {
                            fwrite($file, $ID." ".$args[2]."\n");
                        } else {
                             return $this->display_message(FALSE, self::BAD_PERMISSIONS);
                        }
                    } else {
                        if ($file = fopen(dirname(__FILE__)."/".self::COMMIT_FOLDER."/".self::COMMIT_FILE, "a+")) {
                            fseek($file, -1, SEEK_END);
                            $pos = ftell($file);
                            $lastline = "";
                            while (((($C = fgetc($file)) != "\n") && ($pos > -1)) || strlen($lastline) < 2) {
                                $lastline = $C.$lastline;
                                fseek($file, --$pos);
                            }
                            $explode = explode(" ", $lastline);
                            var_dump($explode);
                            $ID = intval($explode[0]);
                            $ID += 1;
                            fwrite($file, $ID." ".$args[2]."\n");
                        } else {
                            return $this->display_message(TRUE, self::BAD_PERMISSIONS);
                        }
                    }
                
                    fclose($file);

                    $archiver = new MyTar();
 
                    $archiver->archive(dirname(__FILE__)."/".basename(dirname(dirname(__FILE__))), dirname(__FILE__)."/".self::COMMIT_FOLDER."/".$ID);
                } else {
                    return $this->display_message(FALSE, self::MISSING_MESSAGE);
                }
            } else {
                return $this->display_message(TRUE, self::NOT_GIT_FOLDER);
            }
            
            return 0;
        }
        
        private function log($args) {
            if (file_exists(dirname(__FILE__)."/".self::COMMIT_FOLDER."/".self::COMMIT_FILE)) {
                if ($file = fopen(dirname(__FILE__)."/".self::COMMIT_FOLDER."/".self::COMMIT_FILE, "r+")) {
                    while(!feof($file)) {
                        print(fread($file, 1024*8));
                    }
                } else {
                    return $this->display_message(TRUE, self::BAD_PERMISSIONS);
                }
            } else {
                return $this->display_message(FALSE, self::NO_COMMITS);
            }
            return 0;
        }
        
        private function status($args) {
            echo self::STATUS_MODIFIED."\n";
            echo self::STATUS_UNTRACKED."\n";
            $this->$files = array();
            $this->display_untracked_files(dirname(dirname(__FILE__)));
            usort($this->$files, array('MyGit','compare_names'));
            foreach ($this->$files as $file) {
                echo $file."\n";
            }
            echo self::STATUS_DELETED."\n";
        }
        
        private static function compare_names($a, $b)
        {
            if (strtolower($a) == strtolower($b)) {
                return 0;
            }
            return (strtolower($a) < strtolower($b)) ? -1 : 1;
        }
        
        private function display_untracked_files($dir) {
            if ($opened_dir = opendir($dir)) {
                while (($filename = readdir($opened_dir)) !== false) {
                    if ($filename != "." && $filename != ".." && $filename !== self::PARENT_FOLDER) {
                        if (is_dir($dir."/".$filename."/")) {
                            $this->display_untracked_files($dir."/".$filename);
                        } else if (!file_exists(dirname(__FILE__)."/".basename(dirname(dirname(__FILE__)))."/".$filename)) {
                            array_push($this->$files, substr($dir."/".$filename, strlen(dirname(dirname(__FILE__))) + 1, strlen($dir."/".$filename)));
                        }
                    }
                }
                closedir($opened_dir);
            }
        }
    }
    
    class MyTar {
        private $extension = ".myGitLight";
        private $magic = "@MyTar__scriptFDFSDFDCSDSFREWScript@";
        private $header = array();
 
        public function __construct() {

        }
        
        public function archive($folder, $path) {
            $this->create_archive($folder, $path, $this->$header);
        }
        
        private function create_archive($folder, $path, $header) {
            $tarbal = fopen($path.$this->$extension, 'w');
            
     
            $this->list_files($folder, $folder, 0, $tarbal, $header, false);
                
            fwrite($tarbal, $this->$magic);
            //We reserve enough space to rewrite the header after we got all the informations about the files
            for ($i = 0; $i < strlen(json_encode($header)) * 3; ++$i) {
                fwrite($tarbal, '0');
            }
            
            $this->list_files($folder, $folder, 0, $tarbal, $header, true);
                
            fseek($tarbal, 0);
            fwrite($tarbal, $this->$magic.json_encode($header).$this->$magic);
            
            
            fclose($tarbal);
        }
        
        
        private function list_files($dir, $raw_filename, $level, $handler, &$header, $write) {
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
                                $this->list_files($dir."/".$filename."/", $filename, ++$level, $handler, $header[$raw_filename], $write);
                                //list_files($dir."/".$filename."/", $filename, ++$level, $handler, set_directory($dir, $header), $write);
                            } else {
                                $content = $this->get_file_info($dir."/".$filename);
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
                $content = $this->get_file_info($dir.$filename);
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
        
        private function set_directory($dir, &$header) {
            $directories = explode("/", $dir);
            
            var_dump($directories);
            $new_header = $header;
            
            foreach ($directories as $folder) {
                $new_header[$folder] = NULL;
                $new_header = $new_header[$folder];
            }
            
            return $new_header;
        }
        
        private function display_file_info($filename, $level) {
            for ($i = 0; $i <= $level; ++$i) {
                echo "\t";
            }
            echo $filename."\n";
        }
        
        private function get_file_info($filename) {
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
    }
?>
