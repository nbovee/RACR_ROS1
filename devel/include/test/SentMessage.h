// Generated by gencpp from file test/SentMessage.msg
// DO NOT EDIT!


#ifndef TEST_MESSAGE_SENTMESSAGE_H
#define TEST_MESSAGE_SENTMESSAGE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace test
{
template <class ContainerAllocator>
struct SentMessage_
{
  typedef SentMessage_<ContainerAllocator> Type;

  SentMessage_()
    : sender()
    , content()  {
    }
  SentMessage_(const ContainerAllocator& _alloc)
    : sender(_alloc)
    , content(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _sender_type;
  _sender_type sender;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _content_type;
  _content_type content;





  typedef boost::shared_ptr< ::test::SentMessage_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::test::SentMessage_<ContainerAllocator> const> ConstPtr;

}; // struct SentMessage_

typedef ::test::SentMessage_<std::allocator<void> > SentMessage;

typedef boost::shared_ptr< ::test::SentMessage > SentMessagePtr;
typedef boost::shared_ptr< ::test::SentMessage const> SentMessageConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::test::SentMessage_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::test::SentMessage_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::test::SentMessage_<ContainerAllocator1> & lhs, const ::test::SentMessage_<ContainerAllocator2> & rhs)
{
  return lhs.sender == rhs.sender &&
    lhs.content == rhs.content;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::test::SentMessage_<ContainerAllocator1> & lhs, const ::test::SentMessage_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace test

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::test::SentMessage_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::test::SentMessage_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::test::SentMessage_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::test::SentMessage_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::test::SentMessage_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::test::SentMessage_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::test::SentMessage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "b2e1a1fbf660d36f0c4ce4c3ed50a434";
  }

  static const char* value(const ::test::SentMessage_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xb2e1a1fbf660d36fULL;
  static const uint64_t static_value2 = 0x0c4ce4c3ed50a434ULL;
};

template<class ContainerAllocator>
struct DataType< ::test::SentMessage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "test/SentMessage";
  }

  static const char* value(const ::test::SentMessage_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::test::SentMessage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string sender\n"
"string content\n"
;
  }

  static const char* value(const ::test::SentMessage_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::test::SentMessage_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.sender);
      stream.next(m.content);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SentMessage_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::test::SentMessage_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::test::SentMessage_<ContainerAllocator>& v)
  {
    s << indent << "sender: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.sender);
    s << indent << "content: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.content);
  }
};

} // namespace message_operations
} // namespace ros

#endif // TEST_MESSAGE_SENTMESSAGE_H
