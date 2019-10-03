#ifndef note_h
#define note_h


class Note {
  public:
    Note (
      int pitch, 
      int velocity, 
      int length,
      int channel
    ): m_pitch(pitch), m_velocity(velocity), m_length(length), m_channel(channel) {
      m_ended = false;
    }
    int m_pitch;
    int m_velocity;
    int m_length;
    int m_channel;
    boolean m_ended;

    void update () {
      // Serial.println("Note updating");
      m_length--;
      
      if (m_length <= 0) {
        m_ended = true;
      }
    };
};

#endif