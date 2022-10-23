/*
 * This file is part of libnunchuk (https://github.com/nunchuk-io/libnunchuk).
 * Copyright (c) 2020 Enigmo.
 *
 * libnunchuk is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * libnunchuk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libnunchuk. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NUNCHUKMATRIX_INCLUDE_H
#define NUNCHUKMATRIX_INCLUDE_H

#include <nunchuk.h>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include "tap_protocol/cktapcard.h"

namespace nunchuk {

class NUNCHUK_EXPORT NunchukMatrixException : public BaseException {
 public:
  static const int SHARED_WALLET_EXISTS = -5001;
  static const int SHARED_WALLET_NOT_FOUND = -5002;
  static const int EVENT_NOT_FOUND = -5003;
  static const int TRANSACTION_NOT_FOUND = -5004;
  static const int MISMATCHED_NETWORKS = -5005;
  static const int MISMATCHED_KEY_TYPES = -5006;
  static const int DUPLICATE_KEYS = -5007;
  static const int INVALID_KEY = -5008;
  using BaseException::BaseException;
};

class NUNCHUK_EXPORT NunchukMatrixEvent {
 public:
  NunchukMatrixEvent();
  NunchukMatrixEvent(const std::string& from_json);

  std::string get_type() const;
  std::string get_content() const;
  std::string get_event_id() const;
  std::string get_room_id() const;
  std::string get_sender() const;
  time_t get_ts() const;
  std::string to_json() const;

  void set_type(const std::string& value);
  void set_content(const std::string& value);
  void set_event_id(const std::string& value);
  void set_room_id(const std::string& value);
  void set_sender(const std::string& value);
  void set_ts(time_t value);

 private:
  std::string type_;
  std::string content_;
  std::string event_id_;
  std::string room_id_;
  std::string sender_;
  time_t ts_;
};

class NUNCHUK_EXPORT RoomWallet {
 public:
  RoomWallet();
  RoomWallet(const std::string& from_json);

  std::string get_room_id() const;
  std::string get_wallet_id() const;
  std::string get_init_event_id() const;
  std::vector<std::string> get_join_event_ids() const;
  std::vector<std::string> get_leave_event_ids() const;
  std::string get_finalize_event_id() const;
  std::string get_cancel_event_id() const;
  std::string get_ready_event_id() const;
  std::string get_delete_event_id() const;
  std::string get_json_content() const;
  Chain get_chain() const;
  std::string to_json() const;

  void set_room_id(const std::string& value);
  void set_wallet_id(const std::string& value);
  void set_init_event_id(const std::string& value);
  void set_join_event_ids(const std::vector<std::string>& value);
  void set_leave_event_ids(const std::vector<std::string>& value);
  void add_join_event_id(const std::string& value);
  void add_leave_event_id(const std::string& value);
  void set_finalize_event_id(const std::string& value);
  void set_cancel_event_id(const std::string& value);
  void set_ready_event_id(const std::string& value);
  void set_delete_event_id(const std::string& value);
  void set_json_content(const std::string& value);
  void set_chain(const Chain& value);
  void merge(const RoomWallet& value);

 private:
  std::string room_id_;
  std::string wallet_id_;
  std::string init_event_id_;
  std::vector<std::string> join_event_ids_;
  std::vector<std::string> leave_event_ids_;
  std::string finalize_event_id_;
  std::string cancel_event_id_;
  std::string ready_event_id_;
  std::string delete_event_id_;
  std::string json_content_;
  Chain chain_;
};

class NUNCHUK_EXPORT RoomTransaction {
 public:
  RoomTransaction();
  RoomTransaction(const std::string& from_json);

  std::string get_room_id() const;
  std::string get_tx_id() const;
  std::string get_wallet_id() const;
  std::string get_init_event_id() const;
  std::vector<std::string> get_sign_event_ids() const;
  std::vector<std::string> get_reject_event_ids() const;
  std::string get_broadcast_event_id() const;
  std::string get_cancel_event_id() const;
  std::string get_ready_event_id() const;
  Transaction get_tx() const;
  Chain get_chain() const;
  std::string to_json() const;

  void set_room_id(const std::string& value);
  void set_tx_id(const std::string& value);
  void set_wallet_id(const std::string& value);
  void set_init_event_id(const std::string& value);
  void set_sign_event_ids(const std::vector<std::string>& value);
  void set_reject_event_ids(const std::vector<std::string>& value);
  void add_sign_event_id(const std::string& value);
  void add_reject_event_id(const std::string& value);
  void set_broadcast_event_id(const std::string& value);
  void set_cancel_event_id(const std::string& value);
  void set_ready_event_id(const std::string& value);
  void set_tx(const Transaction& value);
  void set_chain(const Chain& value);

 private:
  std::string room_id_;
  std::string tx_id_;
  std::string wallet_id_;
  std::string init_event_id_;
  std::vector<std::string> sign_event_ids_;
  std::vector<std::string> reject_event_ids_;
  std::string broadcast_event_id_;
  std::string cancel_event_id_;
  std::string ready_event_id_;
  Transaction tx_;
  Chain chain_;
};

typedef std::function<std::string /* event_id */ (
    const std::string& /* room_id */, const std::string& /* event_type */,
    const std::string& /* event_content */, bool /* ignore_error */)>
    SendEventFunc;

typedef std::function<std::string /* url */ (
    const std::string& /* file_name */, const std::string& /* mine_type */,
    const std::string& /* json_info */, const char* /* data */,
    size_t /* data_length */)>
    UploadFileFunc;

typedef std::function<std::vector<unsigned char> /* file_data */ (
    const std::string& /* file_name */, const std::string& /* mine_type */,
    const std::string& /* json_info */, const std::string& /* mxc_uri */)>
    DownloadFileFunc;

class NUNCHUK_EXPORT NunchukMatrix {
 public:
  NunchukMatrix(const NunchukMatrix&) = delete;
  NunchukMatrix& operator=(const NunchukMatrix&) = delete;

  virtual ~NunchukMatrix();

  virtual NunchukMatrixEvent SendErrorEvent(const std::string& room_id,
                                            const std::string& platform,
                                            const std::string& code,
                                            const std::string& message) = 0;

  virtual NunchukMatrixEvent InitWallet(
      const std::string& room_id, const std::string& name, int m, int n,
      AddressType address_type, bool is_escrow,
      const std::string& description = {},
      const std::vector<SingleSigner>& signers = {}) = 0;
  virtual NunchukMatrixEvent JoinWallet(const std::string& room_id,
                                        const SingleSigner& signer) = 0;
  virtual NunchukMatrixEvent LeaveWallet(const std::string& room_id,
                                         const std::string& join_event_id,
                                         const std::string& reason = {}) = 0;
  virtual NunchukMatrixEvent CancelWallet(const std::string& room_id,
                                          const std::string& reason = {}) = 0;
  virtual NunchukMatrixEvent CreateWallet(const std::unique_ptr<Nunchuk>& nu,
                                          const std::string& room_id) = 0;
  virtual NunchukMatrixEvent DeleteWallet(const std::unique_ptr<Nunchuk>& nu,
                                          const std::string& room_id) = 0;

  virtual NunchukMatrixEvent InitTransaction(
      const std::unique_ptr<Nunchuk>& nu, const std::string& room_id,
      const std::map<std::string, Amount> outputs, const std::string& memo = {},
      const std::vector<UnspentOutput> inputs = {}, Amount fee_rate = -1,
      bool subtract_fee_from_amount = false) = 0;
  virtual NunchukMatrixEvent SignTransaction(const std::unique_ptr<Nunchuk>& nu,
                                             const std::string& init_event_id,
                                             const Device& device) = 0;
  virtual NunchukMatrixEvent SignAirgapTransaction(
      const std::unique_ptr<Nunchuk>& nu, const std::string& init_event_id,
      const std::string& master_fingerprint) = 0;
  virtual NunchukMatrixEvent SignTapsignerTransaction(
      const std::unique_ptr<Nunchuk>& nu, const std::string& init_event_id,
      tap_protocol::Tapsigner* tapsigner, const std::string& cvc) = 0;
  virtual NunchukMatrixEvent RejectTransaction(
      const std::string& init_event_id, const std::string& reason = {}) = 0;
  virtual NunchukMatrixEvent CancelTransaction(
      const std::string& init_event_id, const std::string& reason = {}) = 0;
  virtual NunchukMatrixEvent BroadcastTransaction(
      const std::unique_ptr<Nunchuk>& nu, const std::string& init_event_id) = 0;

  virtual NunchukMatrixEvent Backup(const std::unique_ptr<Nunchuk>& nu) = 0;
  virtual void RegisterAutoBackup(const std::unique_ptr<Nunchuk>& nu,
                                  const std::string& sync_room_id,
                                  const std::string& access_token) = 0;
  virtual void EnableAutoBackup(bool enable) = 0;
  virtual void EnableGenerateReceiveEvent(
      const std::unique_ptr<Nunchuk>& nu) = 0;

  virtual void RegisterFileFunc(UploadFileFunc upload,
                                DownloadFileFunc download) = 0;
  virtual NunchukMatrixEvent UploadFileCallback(
      const std::string& json_info, const std::string& file_url) = 0;
  virtual void DownloadFileCallback(
      const std::unique_ptr<Nunchuk>& nu, const std::string& json_info,
      const std::vector<unsigned char>& file_data,
      std::function<bool /* stop */ (int /* percent */)> progress) = 0;
  virtual void WriteFileCallback(
      const std::unique_ptr<Nunchuk>& nu, const std::string& json_info,
      const std::string& file_path,
      std::function<bool /* stop */ (int /* percent */)> progress) = 0;

  virtual std::vector<RoomWallet> GetAllRoomWallets() = 0;
  virtual bool HasRoomWallet(const std::string& room_id) = 0;
  virtual RoomWallet GetRoomWallet(const std::string& room_id) = 0;
  virtual std::vector<RoomTransaction> GetPendingTransactions(
      const std::string& room_id) = 0;
  virtual RoomTransaction GetRoomTransaction(
      const std::string& init_event_id) = 0;
  virtual NunchukMatrixEvent GetEvent(const std::string& event_id) = 0;
  virtual std::string GetTransactionId(const std::string& event_id) = 0;

  virtual void ConsumeEvent(const std::unique_ptr<Nunchuk>& nu,
                            const NunchukMatrixEvent& event) = 0;
  virtual void ConsumeSyncEvent(
      const std::unique_ptr<Nunchuk>& nu, const NunchukMatrixEvent& event,
      std::function<bool /* stop */ (int /* percent */)> progress) = 0;

 protected:
  NunchukMatrix() = default;
};

std::unique_ptr<NunchukMatrix> MakeNunchukMatrixForAccount(
    const AppSettings& appsettings, const std::string& access_token,
    const std::string& account, const std::string& device_id,
    SendEventFunc sendfunction);

}  // namespace nunchuk

#endif  // NUNCHUKMATRIX_INCLUDE_H
