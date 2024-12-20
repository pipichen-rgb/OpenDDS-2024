// -*- C++ -*-
//
#ifndef DATAREADER_LISTENER_IMPL
#define DATAREADER_LISTENER_IMPL

#include <tests/Utils/DistributedConditionSet.h>

#include <dds/DdsDcpsSubscriptionExtC.h>
#include <dds/DCPS/LocalObject.h>
#include <map>

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class DataReaderListenerImpl
  : public virtual OpenDDS::DCPS::LocalObject<DDS::DataReaderListener>
{
public:
  DataReaderListenerImpl(DistributedConditionSet_rch dcs,
                         const OpenDDS::DCPS::String& actor,
                         long expected);
  virtual ~DataReaderListenerImpl();

  virtual void on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus & status);

  virtual void on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus & status);

  virtual void on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus & status);

  virtual void on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus & status);

  virtual void on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& status);

  virtual void on_data_available(
    DDS::DataReader_ptr reader);

  virtual void on_sample_lost(
    DDS::DataReader_ptr reader,
    const DDS::SampleLostStatus& status);

  bool ok() const
  {
    ACE_Guard<ACE_Thread_Mutex> guard(mutex_);
    return ok_;
  }

private:
  long num_reads() const;
  bool received_all_expected_messages() const;

  DistributedConditionSet_rch dcs_;
  const OpenDDS::DCPS::String actor_;
  const long expected_;
  mutable ACE_Thread_Mutex mutex_;
  bool ok_;
  std::map<int, int> read_instances_message_count_;
};

#endif /* DATAREADER_LISTENER_IMPL  */
