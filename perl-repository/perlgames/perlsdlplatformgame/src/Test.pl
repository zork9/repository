 use SDL;
 use SDL::Video;
 use SDL::Rect;
 use SDL::Surface;
 
 my $screen_width  = 640;
 my $screen_height = 480;
 
 SDL::init(SDL_INIT_VIDEO);
 
 my $screen  = SDL::Video::set_video_mode($screen_width, $screen_height, 32, SDL_SWSURFACE);
 
 my $picture = SDL::Video::load_BMP('./pics/lena.bmp');
 
 die(SDL::get_error) unless $picture;
 
 my $rect    = SDL::Rect->new(0, 0, $screen_width, $screen_height);
 
 SDL::Video::blit_surface( $picture, SDL::Rect->new(0, 0, 256, 256), 
                           $screen,  SDL::Rect->new(0, 0, 640,  480) );
 
 SDL::Video::update_rect( $screen, 0, 0, $screen_width, $screen_height );
 
 sleep(2);
