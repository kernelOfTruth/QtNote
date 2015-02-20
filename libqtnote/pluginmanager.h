#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QDateTime>
#include <QSharedPointer>
#include <QLibrary>

#include "../plugins/qtnoteplugininterface.h"
#include "../plugins/pluginoptionsinterface.h"

namespace QtNote {

class PluginManager : public QObject
{
	Q_OBJECT
public:
	enum LoadStatus {
        LS_Undefined = 0,
        LS_Loaded,
        LS_Initialized,
        LS_Errors = 100,
        LS_NotPlugin = LS_Errors + 1,
        LS_ErrVersion,
        LS_ErrAbi,
		LS_ErrMetadata,
        LS_Unloaded
	};

	enum LoadPolicy {
		LP_Auto,
		LP_Enabled,
		LP_Disabled
	};

	enum PluginFeature {
        RegularPlugin   = 0x1,
        DEIntegration   = 0x2,
        TrayIcon        = 0x4,
        GlobalShortcuts = 0x8
	};
	Q_DECLARE_FLAGS(PluginFeatures, PluginFeature)

	class PluginData
	{
	public:
		typedef QSharedPointer<PluginData> Ptr;

		PluginData() : instance(0), loadStatus(LS_Undefined) {}
		QObject *instance;
		LoadPolicy loadPolicy;
		LoadStatus loadStatus;
		QString fileName;
		QDateTime modifyTime;
		PluginManager::PluginFeatures features;
		PluginMetadata metadata;
	};

	explicit PluginManager(Main *parent);

    template<class T>
    inline T* castInterface(const PluginData::Ptr &pd) const
    {
        if (pd->loadStatus && pd->loadStatus < LS_Errors) {
            return qobject_cast<T*>(pd->instance);
        }
        return 0;
    }

	void loadPlugins();
	inline LoadPolicy loadPolicy(const QString &pluginId) const { return plugins[pluginId]->loadPolicy; }
	inline LoadStatus loadStatus(const QString &pluginId) const { return plugins[pluginId]->loadStatus; }
	inline bool isLoaded(const QString &pluginId) const
	{
		auto ls = plugins[pluginId]->loadStatus;
		return ls && ls < LS_Errors;
	}
	void setLoadPolicy(const QString &pluginId, LoadPolicy lp);
	inline int pluginsCount() const { return plugins.size(); }
	QStringList pluginsIds() const;
	inline const PluginMetadata &metadata(const QString &pluginId) const { return plugins[pluginId]->metadata; }
	inline QString filename(const QString &pluginId) const { return plugins[pluginId]->fileName; }
	QString tooltip(const QString &pluginId) const;
	inline bool canOptionsDialog(const QString &pluginId) const {
		return castInterface<PluginOptionsInterface>(plugins[pluginId]) != 0;
	}
	inline QDialog* optionsDialog(const QString &pluginId) const {
		auto plugin = castInterface<PluginOptionsInterface>(plugins[pluginId]);
        if (plugin) {
			return plugin->optionsDialog();
		}
		return 0;
	}

signals:

public slots:

private:
	Main *qtnote;
	QHash<QString, PluginData::Ptr> plugins;

	LoadStatus loadPlugin(const QString &fileName, PluginData::Ptr &cache, QLibrary::LoadHints loadHints = 0);
    void updateMetadata();
    bool ensureLoaded(PluginData::Ptr pd);
    QString iconsCacheDir() const;
};

}

#endif // PLUGINMANAGER_H
