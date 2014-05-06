class AddAttachmentGpsdatafileToUsers < ActiveRecord::Migration
  def self.up
    change_table :users do |t|
      t.attachment :gpsdatafile
    end
  end

  def self.down
    drop_attached_file :users, :gpsdatafile
  end
end
