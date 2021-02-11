// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2020, CADEX. All rights reserved.
//
// This file is part of the CAD Exchanger software.
//
// This file may be used under the terms and conditions of the License
// Agreement supplied with the software.
//
// This file is provided "AS IS" WITH NO WARRANTY OF ANY KIND, EITHER EXPRESSED
// OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE WARRANTY OF DESIGN,
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// ****************************************************************************


#ifndef _Base_ProgressStatus_HeaderFile
#define _Base_ProgressStatus_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/Base_SharedPtr.hxx>

namespace cadex {

namespace internal {
class Base_ProgressStatusImpl;
class Base_ProgressStatusObserverImpl;
}

class Base_ProgressStatus
{
public:

    //! Defines a type of the progress status value and ranges.
    typedef float       ValueType;

    //! Defines a type of the progress status value and ranges.
    typedef ValueType   value_type;

    class Observer
    {
    public:

        //! Constructor.
        __CADEX_EXPORT Observer();

        //! Constructor.
        __CADEX_EXPORT Observer (const Observer& theOther);

        //! Destructor.
        __CADEX_EXPORT virtual ~Observer();

        //! Assignment operator.
        __CADEX_EXPORT Observer& operator= (const Observer& theOther);


        //! A callback called when the progress status has changed its value.
        /*! Subclasses must redefine this method to process this event.*/
        virtual void ChangedValue (const Base_ProgressStatus& theStatus) = 0;

        //! A callback called when the progress status object is being destructed.
        /*! Subclasses must redefine this method to process this event.*/
        virtual void Completed (const Base_ProgressStatus& theStatus) = 0;

        __CADEX_EXPORT virtual void Canceled (const Base_ProgressStatus& theStatus);


        //multi-threading related API

        //! Sets the current thread as the only thread sending notifications.
        __CADEX_EXPORT void SetNotifyingThread();

        //! Sets the same notification thread as used by \a theOther observer.
        __CADEX_EXPORT void SetNotifyingThread (const Observer& theOther);

        //! Enables sending notifications from any thread.
        __CADEX_EXPORT void SetAllNotifyingThreads();

        //! Returns true if notifications can be send from the current thread.
        __CADEX_EXPORT bool CanBeNotifiedFromThisThread() const;

    private:
        static const size_t myImplSize = 32;
        union ImplMemory
        {
            void*       myAlign;
            char        myBuf[myImplSize];
        }   myImplMemory;

        const cadex::internal::Base_ProgressStatusObserverImpl& Impl() const;
        cadex::internal::Base_ProgressStatusObserverImpl& Impl();
    };

    class CancellationChecker
    {
    public:
        //! Destructor.
        __CADEX_EXPORT virtual ~CancellationChecker();

        //! Returns true if the operation has been canceled.
        /*! The subclasses must redefine this operator to implement required behavior.*/
        virtual bool operator()() const = 0;
    };

    //! Constructor.
    __CADEX_EXPORT Base_ProgressStatus();

    //! Constructor.
    __CADEX_EXPORT Base_ProgressStatus (const Base_ProgressStatus& theOther);

    //! Constructor.
    __CADEX_EXPORT Base_ProgressStatus (
        const std::shared_ptr<internal::Base_ProgressStatusImpl>& theImpl);

    //! Destructor.
    __CADEX_EXPORT ~Base_ProgressStatus();

    //! Assignment operator.
    __CADEX_EXPORT Base_ProgressStatus& operator= (const Base_ProgressStatus& theOther);

    //! Returns a current value.
    /*! The values is in the range [0, 100].*/
    __CADEX_EXPORT value_type Value() const;

    //! Returns a minimum value of the progress status.
    /*! By convention, returns 0.*/
    static value_type MinValue() { return 0; }

    //! Returns a maximum value of the progress status.
    /*! By convention, returns 100.*/
    static value_type MaxValue() { return 100; }

    //! Adds an observer that will be notified when the progress status has changed.
    __CADEX_EXPORT void Register (Observer& theObserver,
        value_type theValueThreshold = 0.1f, unsigned int theTimeThreshold = 20U);

    //! Removes a previously added observer.
    __CADEX_EXPORT void Unregister (const Observer& theObserver);

    __CADEX_EXPORT void SetCancellationChecker (const CancellationChecker& theChecker);
    __CADEX_EXPORT void RemoveCancellationChecker();

    __CADEX_EXPORT void Cancel();

    __CADEX_EXPORT bool WasCanceled() const;

    //! Returns an internal implementation object.
    /*! \internal */
    const std::shared_ptr<internal::Base_ProgressStatusImpl>& Impl() const { return myImpl; }

private:
    std::shared_ptr<internal::Base_ProgressStatusImpl>  myImpl;
};

__CADEX_EXPORT bool operator== (const Base_ProgressStatus& theV1,
    const Base_ProgressStatus& theV2);

}

#endif
