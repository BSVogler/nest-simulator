#ifndef ASCII_LOGGER_H
#define ASCII_LOGGER_H

#include <fstream>

#include "logger.h"

namespace nest
{

class ASCIILogger : public Logger
{
public:
  ASCIILogger()
    : files_()
  {
  }

  ~ASCIILogger() throw()
  {
  }

  void signup( const int virtual_process, const RecordingDevice& device );
  void initialize();
  void finalize();
  void write_event( const RecordingDevice& device, const Event& event );
  void write_value( const RecordingDevice& device, const double& value );
  void write_end( const RecordingDevice& device );

private:
  const std::string build_filename_( const int& vp, const int& gid ) const;

  struct Parameters_
  {
    long precision_;

    std::string file_ext_;      //!< the file name extension to use, without .
    long fbuffer_size_;         //!< the buffer size to use when writing to file
    long fbuffer_size_old_;     //!< the buffer size to use when writing to file (old)
    bool close_after_simulate_; //!< if true, finalize() shall close the stream
    bool flush_after_simulate_; //!< if true, finalize() shall flush the stream

    Parameters_();

    void get( const ASCIILogger&, DictionaryDatum& ) const;
    void set( const ASCIILogger&, const DictionaryDatum& );
  };

  Parameters_ P_;

  // one map for each virtual process,
  // in turn containing one ostream for everydevice
  typedef std::map< int, std::map< int, std::ofstream* > > file_map;
  file_map files_;
};

} // namespace

#endif // ASCII_LOGGER_H
