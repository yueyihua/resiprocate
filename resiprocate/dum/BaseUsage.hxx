#if !defined(RESIP_BASEUSAGE_HXX)
#define RESIP_BASEUSAGE_HXX

#include "resiprocate/os/compat.hxx"
#include "resiprocate/os/BaseException.hxx"
#include <cassert>
namespace resip
{

class DialogUsageManager;
class Dialog;
class SipMessage;

class BaseUsage
{
   public:
      class Exception : public BaseException
      {
         public:
            Exception(const Data& msg,
                      const Data& file,
                      int line)
               : BaseException(msg, file, line)
            {}
            
            virtual const char* name() const {return "BaseUsage::Exception";}
      };

      class Handle
      {
         public:
            typedef UInt64 Id;
         protected:
            Handle(DialogUsageManager& dum);
            // throws if not found
            BaseUsage* get();
         private:
            DialogUsageManager* mDum;
            Id mId;
            friend class DialogUsageManager;
            static UInt64 getNext();
      };

      BaseUsage(DialogUsageManager& dum, Dialog& dialog);
      virtual ~BaseUsage();

      SipMessage* makeInviteSession();
      SipMessage* makeSubscription();
      SipMessage* makeRefer();
      SipMessage* makePublication();
      SipMessage* makeRegistration();
      SipMessage* makeOutOfDialogRequest();

      // to send a request on an existing dialog (made from make... methods above)
      void send(const SipMessage& request);
      
      DialogUsageManager& dum();
      Dialog& dialog();
      
      virtual void end()=0;
      virtual void dispatch(const SipMessage& msg) = 0;
      virtual BaseUsage::Handle getBaseHandle() = 0;

   private:
      DialogUsageManager& mDum;
      Dialog& mDialog;
};
 
}

#endif
