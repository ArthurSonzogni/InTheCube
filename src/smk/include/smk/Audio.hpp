#ifndef SMK_AUDIO
#define SMK_AUDIO

namespace smk {

// Initialize OpenAL.
class Audio {
 public:
  Audio() { IncreaseRef();}
  ~Audio() { DecreaseRef(); }

  Audio(const Audio&) { IncreaseRef(); }
  Audio(Audio&&) { IncreaseRef(); }

 private:
  void IncreaseRef();
  void DecreaseRef();
};

}  // namespace smk

#endif /* end of include guard: SMK_AUDIO */
