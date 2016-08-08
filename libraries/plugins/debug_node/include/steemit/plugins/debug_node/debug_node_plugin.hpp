
#pragma once

#include <steemit/app/plugin.hpp>

#include <fc/variant_object.hpp>

#include <map>
#include <fstream>

namespace steemit { namespace chain {
   struct signed_block;
} }

namespace graphene { namespace db {
   struct object_id_type;
   class object;
} }

namespace steemit { namespace plugin { namespace debug_node {

class debug_node_plugin : public steemit::app::plugin
{
   public:
      debug_node_plugin();
      virtual ~debug_node_plugin();

      virtual std::string plugin_name()const override;
      virtual void plugin_initialize( const boost::program_options::variables_map& options ) override;
      virtual void plugin_startup() override;
      virtual void plugin_shutdown() override;

      void debug_update( const fc::variant_object& update );
      uint32_t debug_generate_blocks( const std::string& debug_key, uint32_t count );
      uint32_t debug_generate_blocks_until( const std::string& debug_key, const fc::time_point_sec& head_block_time, bool generate_sparsely );

      void set_json_object_stream( const std::string& filename );
      void flush_json_object_stream();

   private:
      void on_changed_objects( const std::vector<graphene::db::object_id_type>& ids );
      void on_removed_objects( const std::vector<const graphene::db::object*> objs );
      void on_applied_block( const chain::signed_block& b );

      void apply_debug_updates();

      std::map<chain::public_key_type, fc::ecc::private_key> _private_keys;

      std::shared_ptr< std::ofstream > _json_object_stream;
      boost::signals2::scoped_connection _applied_block_conn;
      boost::signals2::scoped_connection _changed_objects_conn;
      boost::signals2::scoped_connection _removed_objects_conn;

      std::map< chain::block_id_type, std::vector< fc::variant_object > > _debug_updates;
};

} } }
