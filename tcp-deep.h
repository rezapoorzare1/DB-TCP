/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Author: Reza Poorzare <reza.poorzare@upc.edu>
 *
 * Anna Calveras <anna.calveras@upc.edu>, Supervisor

 */


#ifndef TCPdeep_H
#define TCPdeep_H

#include "ns3/tcp-congestion-ops.h"
#include "ns3/tcp-recovery-ops.h"





namespace ns3 {

/**
 * \ingroup congestionOps
 *
 * \brief An implementation of TCP deep
 
 */

class Tcpdeep : public TcpNewReno
{
public:




  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  /**
   * Create an unbound tcp socket.
   */
  Tcpdeep (void);




   double setThreshold (double th);

   double returnrtt ();


   double returntmp ();


   double returntargetedvscwnd ();


   double returndiff ();





  /**
   * \brief Copy constructor
   * \param sock the object to copy
   */
  Tcpdeep (const Tcpdeep& sock);
  virtual ~Tcpdeep (void);

  virtual std::string GetName () const;

  /**
   * \brief Compute RTTs needed to execute deep algorithm
   *
   * \param segmentsAcked count of segments ACKed
   * \param rtt last RTT
   *
   */
  virtual void PktsAcked (Ptr<TcpSocketState> tcb, uint32_t segmentsAcked,
                          const Time& rtt);

  /**
   * \brief Enable/disable deep algorithm depending on the congestion state
   *
   * We only start a deep cycle when we are in normal congestion state (CA_OPEN state).
   *
   * \param tcb internal congestion state
   * \param newState new congestion state to which the TCP is going to switch
   */
  virtual void CongestionStateSet (Ptr<TcpSocketState> tcb,
                                   const TcpSocketState::TcpCongState_t newState);

  /**
   * \param tcb internal congestion state
   * \param segmentsAcked count of segments ACKed
   */
  virtual void IncreaseWindow (Ptr<TcpSocketState> tcb, uint32_t segmentsAcked);

  /**
   * \param tcb internal congestion state
   * \param bytesInFlight bytes in flight
   *
   */
  virtual uint32_t GetSsThresh (Ptr<const TcpSocketState> tcb,
                                uint32_t bytesInFlight);

  virtual Ptr<TcpCongestionOps> Fork ();

protected:
private:
  /**
   * \brief Enable deep algorithm to start taking deep samples
   *
   * deep algorithm is enabled in the following situations:
   * 1. at the establishment of a connection
   * 2. after an RTO
   * 3. after fast recovery
   * 4. when an idle connection is restarted
   *
   * \param tcb internal congestion state
   */
  void Enabledeep (Ptr<TcpSocketState> tcb);

  /**
   * \brief Stop taking deep samples
   */
  void Disabledeep ();

private:
  Time m_baseRtt;                    //!< Minimum of all deep RTT measurements seen during connection
  Time m_minRtt;                     //!< Minimum of all RTT measurements within last RTT
  uint32_t m_cntRtt;                 //!< Number of RTT measurements during last RTT
  bool m_doingdeepNow;              //!< If true, do deep for this RTT
  SequenceNumber32 m_begSndNxt;      //!< Right edge during last RTT



};

} // namespace ns3

#endif // TCPdeep_H
